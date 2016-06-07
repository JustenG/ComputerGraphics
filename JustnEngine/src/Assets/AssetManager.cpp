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

void AssetManager::LoadTexture(std::string filePath, std::string name, bool texWrapping)
{
	Texture* tempTexture = new Texture();
	tempTexture->LoadTexture(filePath, texWrapping);
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
	if (m_meshFiles.find(name) == m_meshFiles.end())
		return nullptr;
	else
		return  m_meshFiles[name];
}
template<>
Material* AssetManager::GetAsset<Material>(std::string name)
{
	if (m_materials.find(name) == m_materials.end())
		return nullptr;
	else
		return m_materials[name];
}
template<>
Shader* AssetManager::GetAsset<Shader>(std::string name)
{
	if (m_shaders.find(name) == m_shaders.end())
		return nullptr;
	else
		return m_shaders[name];
}
template<>
Texture* AssetManager::GetAsset<Texture>(std::string name)
{
	if (m_textures.find(name) == m_textures.end())
		return nullptr;
	else
		return m_textures[name];
}

