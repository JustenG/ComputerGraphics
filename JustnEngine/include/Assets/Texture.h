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

private:

	void onBind() override;
	void onUnbind() override;

	unsigned int m_uiTextureID;
	
	//TODO: Add additional texture options
	int m_iTextureFormat;
	int m_iImageWidth;
	int m_iImageHeight;

	unsigned int m_uiTextureSlot;
};
