#pragma once

#include<string>

class Texture
{
public:
	Texture();
	~Texture();

	void SetTextureSlot(unsigned int uiSlot);
private:

	void LoadWithSTBImage(std::string& strFilePath);

	unsigned int m_uiTextureID;
	
	//TODO: Add additional texture options
	int m_iTextureFormat;
	int m_iImageWidth;
	int m_iImageHeight;

	unsigned int m_uiTextureSlot;
};
