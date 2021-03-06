#pragma once

#include <string>
#include <map>

class Asset;
class MeshFile;
class Shader;
class Material;
class Texture;

class AssetManager
{
public:
	static AssetManager* GetInstance();
	~AssetManager();
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

	template<typename T>
	T* GetAsset(std::string name);

	void AssetManager::LoadMeshFile(std::string filePath, std::string name);
	void AssetManager::LoadTexture(std::string filePath, std::string name, bool texWrapping = false);
	void AssetManager::LoadShader(std::string vertexPath, std::string fragmentPath, std::string name);
	void AssetManager::CreateMaterial(std::string name);


private:
	AssetManager();
	static AssetManager* m_instance;

	std::map<std::string, MeshFile*> m_meshFiles;
	std::map<std::string, Shader*> m_shaders;
	std::map<std::string, Material*> m_materials;
	std::map<std::string, Texture*> m_textures;


};