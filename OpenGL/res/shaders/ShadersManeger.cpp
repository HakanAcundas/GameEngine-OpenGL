#include "ShadersManeger.h"

ShaderManeger::ShaderManeger()
{

}

ShaderManeger::~ShaderManeger()
{

}

ShaderSources ShaderManeger::ParseShaders(std::string& filePath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType shaderType = ShaderType::NONE;
	
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				shaderType = ShaderType::VERTEX;

			else if (line.find("fragment") != std::string::npos)
				shaderType = ShaderType::FRAGMENT;
		}
		else
			ss[(int)shaderType] << line << '\n';
	}
	std::cout << "VERTEX SHADER\n" << ss[0].str() << std::endl << "FRAGMENT SHADER\n" << ss[1].str() << std::endl;
	return { ss[0].str(), ss[1].str() };
}

unsigned int ShaderManeger::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* massege = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, massege);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
		<< "shader!" << std::endl;
		std::cout << massege << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int ShaderManeger::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shaderProgram;
}

void ShaderManeger::Use(unsigned int shaderID)
{
	glUseProgram(shaderID);
}

void ShaderManeger::SetBool(unsigned int shaderID, const std::string& uniformName, bool value)
{
	glUniform1i(glGetUniformLocation(shaderID, uniformName.c_str()), value);
}

void ShaderManeger::SetInt(unsigned int shaderID, const std::string& uniformName, bool value)
{
	glUniform1d(glGetUniformLocation(shaderID, uniformName.c_str()), value);
}

void ShaderManeger::SetFloat(unsigned int shaderID, const std::string& uniformName, bool value)
{
	glUniform1f(glGetUniformLocation(shaderID, uniformName.c_str()), value);
}

void ShaderManeger::SetVec2(unsigned int shaderID, const std::string& uniformName, float x, float y)
{
	glUniform2f(glGetUniformLocation(shaderID, uniformName.c_str()), x, y);
}

void ShaderManeger::SetVec2(unsigned int shaderID, const std::string& uniformName, const glm::vec2& value)
{
	glUniform2fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, &value[0]);
}

void ShaderManeger::SetVec3(unsigned int shaderID, const std::string& uniformName, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(shaderID, uniformName.c_str()), x, y, z);
}

void ShaderManeger::SetVec3(unsigned int shaderID, const std::string& uniformName, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, &value[0]);
}

void ShaderManeger::SetVec4(unsigned int shaderID, const std::string& uniformName, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(shaderID, uniformName.c_str()), x, y, z, w);
}

void ShaderManeger::SetVec4(unsigned int shaderID, const std::string& uniformName, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, &value[0]);
}

void ShaderManeger::SetMat2(unsigned int shaderID, const std::string& uniformName, const glm::mat2& value)
{
	glUniformMatrix2fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderManeger::SetMat3(unsigned int shaderID, const std::string& uniformName, const glm::mat3& value)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
}

void ShaderManeger::SetMat4(unsigned int shaderID, const std::string& uniformName, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, uniformName.c_str()), 1, GL_FALSE, &value[0][0]);
}

