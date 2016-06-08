#include "Assets\MeshFile.h"

#include <FBXFile.h>
#include "all_includes.h"

#include "Assets\Mesh.h"
//To be moved to a GameObjectGenerator
//------------------------------------
#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Components\MeshRenderer.h"
#include "Entitys\EntityManager.h"
#include "Entitys\GameObject.h"
//------------------------------------

MeshFile::MeshFile()
{
	m_pEntityManager = EntityManager::GetInstance();
	m_pComponentManager = ComponentManager::GetInstance();
	m_pShader = nullptr;
}

MeshFile::~MeshFile()
{
}

void MeshFile::onBind()
{
}

void MeshFile::onUnbind()
{
}

void MeshFile::Update()
{

}

void MeshFile::LoadFile(std::string fileName)
{
	SetFilePath(fileName);

	int startOfExtension = fileName.find_last_of('.');
	std::string fileType = fileName.substr(startOfExtension + 1, fileName.length());

	printf("filename");
#ifdef FBX_SUPPORTED
	if (fileType == "fbx")
	{
		LoadFBX(fileName);
	}
#endif
}

#ifdef FBX_SUPPORTED
void MeshFile::LoadFBX(std::string fileName)
{
	//Load FBX File
	m_fbxFile = new FBXFile();
	bool bLoaded = m_fbxFile->load(fileName.c_str());

	//For every
	for (unsigned int i = 0; i < m_fbxFile->getMeshCount(); ++i)
	{
		FBXMeshNode* pMesh = m_fbxFile->getMeshByIndex(i);
		assert(pMesh && "Require at least one mesh in your FBX");
		
		Mesh* pNewMesh = new Mesh();
		m_internalMeshes.push_back(pNewMesh);

		pNewMesh->BuildRenderDataFromLoaderNode(pMesh);
		pNewMesh->BuildMaterialFromLoaderNode(pMesh->m_materials[0],GetFileName() + "_MaterialMesh" + std::to_string(i));
	}
}


//To be moved to a GameObjectGenerator
//------------------------------------
void MeshFile::CreateEntitys()
{
	if (m_pGameObjects.size() != 0)
		return;

	for (unsigned int i = 0; i < m_fbxFile->getMeshCount(); ++i)
	{
		m_pGameObjects.push_back(m_pEntityManager->CreateEntity());
		GameObject* tempObject = m_pGameObjects.back();
		//Get Mesh Name
		std::string name = m_fbxFile->getMeshByIndex(i)->m_name;
		std::string fileName = GetFileName();
		//If Mesh has no name, use file name
		if (name == "")
			name = fileName.substr(0, fileName.find('.'));
		//Set Game Objects Name
		tempObject->SetName(name);
		//Add required components
		tempObject->AddComponent<Transform>();
		tempObject->AddComponent<MeshRenderer>();
		tempObject->GetComponent<MeshRenderer>()->SetMesh(m_internalMeshes[i]);
		tempObject->GetComponent<MeshRenderer>()->SetMaterial(m_internalMeshes[i]->GetMaterial());
		tempObject->GetComponent<MeshRenderer>()->SetShader(m_pShader);
	}
	for (unsigned int i = 0; i < m_fbxFile->getMeshCount(); ++i)
	{
		if (m_fbxFile->getMeshByIndex(i)->m_children.size() != 0)
		{
			SetChildren(m_fbxFile->getMeshByIndex(i), i);
		}
	}
}

void MeshFile::SetChildren(FBXNode* mesh, int parentIndex)
{
	for (unsigned int i = 0; i < mesh->m_children.size(); ++i)
	{
		int childIndex;
		for (unsigned int j = 0; j < m_fbxFile->getMeshCount(); ++j)
		{
			if (m_fbxFile->getMeshByIndex(j)->m_name == mesh->m_children[i]->m_name)
			{
				childIndex = j;
				break;
			}
		}

		m_pGameObjects[parentIndex]->GetComponent<Transform>()->AddChild(m_pGameObjects[childIndex]->GetComponent<Transform>());

		SetChildren(mesh->m_children[i], childIndex);
	}
}
#endif
//------------------------------------