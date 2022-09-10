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
	ShaderManeger();
	~ShaderManeger();

	ShaderSources ParseShaders(std::string& filePath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	void Use() const;
	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, bool value) const;
	void SetFloat(const std::string &name, bool value) const;

	void SetVec2(const std::string &name, float x, float y) const;
	void SetVec2(const std::string &name, const glm::vec2 &value) const;

	void SetVec3(const std::string &name, float x, float y, float z) const;
	void SetVec3(const std::string &name, const glm::vec3 &value) const;

	void SetVec4(const std::string& name, float x, float y, float z, float w) const;
	void SetVec4(const std::string& name, const glm::vec4& value) const;

	void SetMat2(const std::string& name, const glm::mat2 &value) const;
	void SetMat3(const std::string& name, const glm::mat3& value) const;
	void SetMat4(const std::string& name, const glm::mat4& value) const;

private:

};
