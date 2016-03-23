#include "Assets\Asset.h"

Asset::Asset()
{
	m_pAssetManager = AssetManager::GetInstance();
}

std::string Asset::GetFileName()
{
	std::string path(GetFilePath());
	int startOfExtension = GetFilePath().find_last_of('/');
	return path.substr(startOfExtension + 1, path.length() - 4);
	//Check this 
}

void Asset::Bind()
{
	onBind();
}

void Asset::Unbind()
{
	onUnbind();
}

void Asset::SetFilePath(std::string filePath)
{
	m_pFilePath = filePath;
}
std::string Asset::GetFilePath()
{
	return m_pFilePath;
}
