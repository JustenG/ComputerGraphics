#include "Assets/Mesh.h"

#include <FBXFile.h>
#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Rendering\VertexArrayObject.h"
#include "Assets\Shader.h"

Mesh::Mesh()
{


}

Mesh::~Mesh()
{

}

void Mesh::LoadFile(std::string fileName)
{
	int startOfExtension = fileName.find_last_of('.');
	std::string fileType = fileName.substr(startOfExtension + 1, fileName.length());

	if (fileType == "fbx")
	{
		LoadFBX(fileName);
	}

}

void Mesh::LoadFBX(std::string fileName)
{
	FBXFile* fbx = new FBXFile();
	bool bLoaded = fbx->load(fileName.c_str());


	FBXMeshNode* pMesh = fbx->getMeshByIndex(0);
	assert(pMesh && "Require at least one mesh in your FBX");

	BuildRenderDataFromLoaderNode(&m_pRenderObject, pMesh);
	BuildMaterialFromLoaderNode(&m_pMaterial, pMesh->m_material);

	for (unsigned int i = 1; i < fbx->getMeshCount(); ++i)
	{
		Mesh* pNewMesh = new Mesh();
		BuildRenderDataFromLoaderNode(&(pNewMesh->m_pRenderObject), fbx->getMeshByIndex(i));
		BuildMaterialFromLoaderNode(&(pNewMesh->m_pMaterial), fbx->getMeshByIndex(i)->m_material);

		if (m_pShader)
			pNewMesh->SetShader(m_pShader);
		m_internalMeshes.push_back(pNewMesh);
	}

}

void Mesh::BuildRenderDataFromLoaderNode(VertexArrayObject** pRenderData, FBXMeshNode* pMesh)
{
	assert(pMesh);
	assert(pRenderData);

	*pRenderData = new VertexArrayObject();

	(*pRenderData)->CreateVAO<FBXVertex>(m_pData, pMesh->m_vertices.size(), pMesh->m_indices.size(), pMesh->m_vertices.data(), pMesh->m_indices.data());
}

void Mesh::SetShader(Shader* shader)
{
	m_pShader = shader;
}

void Mesh::LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	m_pShader->LoadShader(vertexPath, fragmentPath);
}
