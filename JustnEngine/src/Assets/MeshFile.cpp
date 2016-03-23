#include "Assets\MeshFile.h"

#include <FBXFile.h>
#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Assets\Mesh.h"

MeshFile::MeshFile()
{
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
	int startOfExtension = fileName.find_last_of('.');
	std::string fileType = fileName.substr(startOfExtension + 1, fileName.length());
	printf("filename");

	if (fileType == "fbx")
	{
		LoadFBX(fileName);
	}
}

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

		m_internalMeshes.emplace_back();
		Mesh* pNewMesh = m_internalMeshes.back();

		pNewMesh->BuildRenderDataFromLoaderNode(pMesh);
		pNewMesh->BuildMaterialFromLoaderNode(pMesh->m_materials[0]);
	}
}

void MeshFile::CreateEntitys()
{
	for (unsigned int i = 0; i < m_fbxFile->getMeshCount(); ++i)
	{
		//TODO
		//Create an entity for each mesh
		//Set each entitys mesh renderer's mesh to internal mesh
	}
}