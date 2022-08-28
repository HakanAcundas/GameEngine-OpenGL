#pragma once
#include <gl/glew.h>
#include <string>
#include <iostream>
#include "..\res/vendor/stb_image/stb_image.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void Bind() const;
	void UnBind() const;
	void FreeImageData() const;

	void LoadTexture(std::string& imagePath, int width, int height, int nrChannels);
private:
	unsigned int m_TextureID;
	unsigned char* m_TextureData;
};
