#include "TextureManager.h"

TextureManager::TextureManager()
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

void TextureManager::LoadTexture(std::string& imagePath, int width, int height)
{
	int nrComponents;
	m_TextureData = stbi_load(imagePath.c_str(), &width, &height, &nrComponents, 0);

	if (m_TextureData)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, m_TextureData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(m_TextureData);
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