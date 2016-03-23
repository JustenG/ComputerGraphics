#include "Assets/AssetManager.h"
#include "Assets/MeshFile.h"
#include "Assets/Material.h"
#include "Assets/Shader.h"
#include "Assets/Texture.h"

AssetManager* AssetManager::m_instance = new AssetManager();

AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	//TODO
	//delete all pointers in maps
}

AssetManager * AssetManager::GetInstance()
{
	if (!m_instance)
		m_instance = new AssetManager();

	return m_instance;
};


void AssetManager::LoadMeshFile(std::string filePath, std::string name)
{
	MeshFile* tempMesh = new MeshFile();
	tempMesh->LoadFile(filePath);
	m_meshFiles[name] = tempMesh;
}

void AssetManager::LoadTexture(std::string filePath, std::string name)
{
	Texture* tempTexture = new Texture();
	tempTexture->LoadTexture(filePath);
	m_textures[name] = tempTexture;
}

void AssetManager::LoadShader(std::string vertexPath, std::string fragmentPath, std::string name)
{
	Shader* tempShader = new Shader();
	tempShader->LoadShader(vertexPath, fragmentPath);
	m_shaders[name] = tempShader;
}

void AssetManager::CreateMaterial(std::string name)
{
	Material* tempTexture = new Material();
	m_materials[name] = tempTexture;
}


template<>
MeshFile* AssetManager::GetAsset<MeshFile>(std::string name)
{
	return m_meshFiles[name];
}
template<>
Material* AssetManager::GetAsset<Material>(std::string name)
{
	return m_materials[name];
}
template<>
Shader* AssetManager::GetAsset<Shader>(std::string name)
{
	return m_shaders[name];
}
template<>
Texture* AssetManager::GetAsset<Texture>(std::string name)
{
	return m_textures[name];
}

