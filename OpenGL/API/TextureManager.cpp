#include "TextureManager.h"

TextureManager::TextureManager()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &m_TextureID);
}

void TextureManager::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void TextureManager::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureManager::LoadTexture(std::string& imagePath, int width, int height, int nrChannels)
{
	m_TextureData = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);

	if (m_TextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture!" << std::endl;
	}
}

void TextureManager::TextureFlipVertically()
{
	stbi_set_flip_vertically_on_load(true);
}

void TextureManager::FreeImageData() const
{
	stbi_image_free(m_TextureData);
}