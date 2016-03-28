#pragma once
#include "Assets\Asset.h"

#include <vector>
#include <iostream>
#include <string>
#include "gl_core_4_4.h"

class Mesh;
class Shader;
class FBXFile;
//To be moved to a GameObjectGenerator
//------------------------------------
class EntityManager;
class ComponentManager;
class GameObject;
class FBXNode;
//------------------------------------

class MeshFile : public Asset
{
public:
	MeshFile();
	~MeshFile();

	void LoadFile(std::string fileName);
	void LoadFBX(std::string fileName);
	void SetShader(Shader* shader) { m_pShader = shader; };

	void Update();

	//To be moved to a GameObjectGenerator
	//------------------------------------
	void CreateEntitys();
	void SetChildren(FBXNode* mesh, int parentIndex);
	//------------------------------------

private:

	void onBind() override;
	void onUnbind() override;

	FBXFile* m_fbxFile;
	std::vector<Mesh*> m_internalMeshes;

	//To be moved to a GameObjectGenerator
	//------------------------------------
	EntityManager* m_pEntityManager;
	ComponentManager* m_pComponentManager;
	std::vector<GameObject*> m_pGameObjects;
	//------------------------------------

	Shader* m_pShader;
};

