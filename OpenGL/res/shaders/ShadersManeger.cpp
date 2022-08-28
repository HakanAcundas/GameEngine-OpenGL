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