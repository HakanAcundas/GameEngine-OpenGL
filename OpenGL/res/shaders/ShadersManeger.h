#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <gl/glew.h>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

struct ShaderSources
{
	std::string vertexSource;
	std::string fragmentSource;
};

class ShaderManeger
{
public:
	unsigned int m_ShaderVertexID;
	unsigned int m_ShaderFragmentID;


public:

	ShaderManeger();
	~ShaderManeger();

	ShaderSources ParseShaders(std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	static void Use(unsigned int shaderID);
	static void SetBool(unsigned int shaderID, const std::string & uniformName, bool value);
	static void SetInt(unsigned int shaderID, const std::string & uniformName, int value);
	static void SetFloat(unsigned int shaderID, const std::string & uniformName, float value);

	static void SetVec2(unsigned int shaderID, const std::string & uniformName, float x, float y);
	static void SetVec2(unsigned int shaderID, const std::string & uniformName, const glm::vec2 &value);

	static void SetVec3(unsigned int shaderID, const std::string & uniformName, float x, float y, float z);
	static void SetVec3(unsigned int shaderID, const std::string & uniformName, const glm::vec3 &value);

	static void SetVec4(unsigned int shaderID, const std::string& uniformName, float x, float y, float z, float w);
	static void SetVec4(unsigned int shaderID, const std::string& uniformName, const glm::vec4& value);

	static void SetMat2(unsigned int shaderID, const std::string& uniformName, const glm::mat2 &value);
	static void SetMat3(unsigned int shaderID, const std::string& uniformName, const glm::mat3& value);
	static void SetMat4(unsigned int shaderID, const std::string& uniformName, const glm::mat4& value);

private:

};
