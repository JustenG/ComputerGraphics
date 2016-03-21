#pragma once
#include "Assets\Asset.h"

#include<string>

class Texture : public Asset
{
public:
	Texture();
	~Texture();

	void SetTextureSlot(unsigned int uiSlot);
	void LoadTexture(std::string& strFilePath);

	GLuint GetId() const { return m_uiTextureID; }
	void SetId(GLuint textureId) { m_uiTextureID = textureId; }

private:

	void onBind() override;
	void onUnbind() override;

	GLuint m_uiTextureID;
	GLuint m_uiTextureSlot = 0;
	
	//TODO: Add additional texture options
	int m_iTextureFormat;
	int m_iImageWidth;
	int m_iImageHeight;
};
