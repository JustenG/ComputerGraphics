#include "Assets/Texture.h"

#include "stb_image.h"
#include <assert.h>

#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"

Texture::Texture()
{

}

Texture::~Texture()
{

}

void Texture::onBind()
{
	glActiveTexture(GL_TEXTURE0 + m_uiTextureSlot);
	glBindTexture(GL_TEXTURE_2D, m_uiTextureID);
}

void Texture::onUnbind()
{
	//Do any texture unbinding
}

void Texture::SetTextureSlot(unsigned int uiSlot)
{
	m_uiTextureSlot = uiSlot;
}

void Texture::LoadTexture(std::string& strFilePath)
{
	unsigned char* data = stbi_load(strFilePath.c_str(), &m_iImageWidth, &m_iImageHeight, &m_iTextureFormat, STBI_default);

	if (data == nullptr)
		return;

	GLuint uiTextureFormat = GL_RGB;

	switch (m_iTextureFormat)
	{
	case 1:
		uiTextureFormat = GL_RED;
		break;
	case 2:
		uiTextureFormat = GL_RG;
		break;
	case 3:
		uiTextureFormat = GL_RGB;
		break;
	case 4:
		uiTextureFormat = GL_RGBA;
		break;
	default:
		assert("Unkown texture format");
	}


	glGenTextures(1, &m_uiTextureID);
	glBindTexture(GL_TEXTURE_2D, m_uiTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, uiTextureFormat, m_iImageWidth, m_iImageHeight,	0, uiTextureFormat, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}
