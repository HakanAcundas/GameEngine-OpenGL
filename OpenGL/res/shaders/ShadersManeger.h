#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <gl/glew.h>

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

private:

};
