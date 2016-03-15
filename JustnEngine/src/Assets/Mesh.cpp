#include "Assets\Mesh.h"

#include <FBXFile.h>
#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Rendering\VertexArrayObject.h"
#include "Assets\Shader.h"
#include "Cameras\Camera.h"

Mesh::Mesh()
{
	m_pShader = new Shader();
	m_pMaterial = new Material();
	m_pRenderObject = new VertexArrayObject();

}

Mesh::~Mesh()
{

}

void Mesh::LoadFile(std::string fileName)
{
	int startOfExtension = fileName.find_last_of('.');
	std::string fileType = fileName.substr(startOfExtension + 1, fileName.length());
	printf("filename");

	if (fileType == "fbx")
	{
		//LoadFBX(fileName);
	}

}

void Mesh::onBind()
{
	m_pShader->Bind();
	m_pMaterial->Bind();
	m_pRenderObject->Bind();
}

void Mesh::onUnbind()
{
	m_pRenderObject->Unbind();
	m_pMaterial->Unbind();
	m_pShader->Unbind();
}

void Mesh::Render(Camera* pCamera, bool setUniforms)
{
	if (setUniforms)
	{
		m_pShader->SetProjectionUniform(pCamera->GetProjection());
		m_pShader->SetViewUniform(pCamera->GetView());
		m_pShader->SetProjectionViewUniform(pCamera->GetProjectionView());
		m_pShader->SetProjectionViewModelUniform(pCamera->GetProjectionView());
	}

	Bind();
	m_pRenderObject->DrawObject();
	Unbind();

	//Also need to render each internal mesh - they will be using the same shader
	for (unsigned int i = 0; i < m_internalMeshes.size(); ++i)
	{
		Mesh* pMesh = m_internalMeshes[i];
		pMesh->Render(pCamera,false);
	}
}

void Mesh::LoadFBX(std::string fileName)
{
	FBXFile* fbx = new FBXFile();
	bool bLoaded = fbx->load(fileName.c_str());


	FBXMeshNode* pMesh = fbx->getMeshByIndex(0);
	assert(pMesh && "Require at least one mesh in your FBX");

	BuildRenderDataFromLoaderNode(&m_pRenderObject, pMesh);
	BuildMaterialFromLoaderNode(&m_pMaterial, pMesh->m_materials[0]);

	for (unsigned int i = 1; i < fbx->getMeshCount(); ++i)
	{
		Mesh* pNewMesh = new Mesh();
		BuildRenderDataFromLoaderNode(&(pNewMesh->m_pRenderObject), fbx->getMeshByIndex(i));
		BuildMaterialFromLoaderNode(&(pNewMesh->m_pMaterial), fbx->getMeshByIndex(i)->m_materials[0]);

		if (m_pShader)
			pNewMesh->SetShader(m_pShader);
		m_internalMeshes.push_back(pNewMesh);
	}

}

void Mesh::BuildRenderDataFromLoaderNode(VertexArrayObject** pRenderObject, FBXMeshNode* pMesh)
{
	assert(pMesh);
	assert(pRenderObject);

	(*pRenderObject)->CreateVAO<FBXVertex>(pMesh->m_vertices.size(), pMesh->m_indices.size(), pMesh->m_vertices.data(), pMesh->m_indices.data());
}

void Mesh::SetShader(Shader* shader)
{
	m_pShader = shader;
}

void Mesh::LoadShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	m_pShader->LoadShader(vertexPath, fragmentPath);
}
