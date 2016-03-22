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
	m_pShader = nullptr;
	m_pMaterial = nullptr;
	m_pRenderObject = new VertexArrayObject();
}

Mesh::~Mesh()
{
	delete m_pRenderObject;
}

void Mesh::LoadFile(std::string fileName)
{
	int startOfExtension = fileName.find_last_of('.');
	std::string fileType = fileName.substr(startOfExtension + 1, fileName.length());
	printf("filename");

	if (fileType == "fbx")
	{
		LoadFBX(fileName);
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


void Mesh::Render(Transform transform, Camera camera, std::vector<Light> lights, int shadowMap, bool setUniforms)
{
	if (setUniforms)
	{
		m_pShader->SetModelUniform(transform.GetMatrix());

		m_pShader->SetCameraPositionUniform(camera.GetPosition());
		m_pShader->SetProjectionUniform(camera.GetProjection());
		m_pShader->SetViewUniform(camera.GetView());
		m_pShader->SetProjectionViewUniform(camera.GetProjectionView());
		m_pShader->SetProjectionViewModelUniform(camera.GetProjectionView());

		m_pShader->SetUniform("specPow", m_specularPower);

		m_pShader->SetUniform("lights", lights);
		m_pShader->SetUniform("shadowMap", shadowMap);
	}

	Bind();
	m_pRenderObject->DrawObject();
	Unbind();

	//Also need to render each internal mesh - they will be using the same shader
	for (unsigned int i = 0; i < m_internalMeshes.size(); ++i)
	{
		Mesh* pMesh = m_internalMeshes[i];
		pMesh->Render(transform, camera, lights, shadowMap, false);
	}
}

void Mesh::Render(Light light, bool setUniforms)
{
	Shader* shader = light.GetShader();

	if (setUniforms)
	{
		shader->SetCameraPositionUniform(light.GetPosition());
		shader->SetProjectionUniform(light.GetProjection());
		shader->SetViewUniform(light.GetView());
		shader->SetProjectionViewUniform(light.GetProjectionView());
		shader->SetProjectionViewModelUniform(light.GetProjectionView());
	}

	shader->Bind();
	m_pRenderObject->Bind();
	m_pRenderObject->DrawObject();
	m_pRenderObject->Unbind(); 
	shader->Unbind();

	//Also need to render each internal mesh - they will be using the same shader
	for (unsigned int i = 0; i < m_internalMeshes.size(); ++i)
	{
		Mesh* pMesh = m_internalMeshes[i];
		pMesh->Render(light, false);
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
void Mesh::SetMaterial(Material* material)
{
	m_pMaterial = material;
}
