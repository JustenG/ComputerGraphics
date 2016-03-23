#pragma once
#include <string>
#include "gl_core_4_4.h"

#include "Assets\AssetManager.h"

//sclass AssetManager;

class Asset
{
public:
	Asset();
	virtual ~Asset() {};

	Asset(Asset&& other) = delete;
	Asset& operator=(Asset&& other) = delete;
	Asset(const Asset& other) = delete; //No copy
	Asset& operator=(Asset& other) = delete;

	void Bind();
	void Unbind();

	void SetFilePath(std::string filePath);
	std::string GetFilePath();
	std::string GetFileName();

protected:
	virtual void onBind() = 0;
	virtual void onUnbind() = 0;

	AssetManager* m_pAssetManager;

private:
	 
	std::string m_pFilePath;

};