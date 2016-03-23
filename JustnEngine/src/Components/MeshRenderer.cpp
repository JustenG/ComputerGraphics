#include "Components\MeshRenderer.h"

#include <FBXFile.h>
#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "Assets\Mesh.h"
#include "Assets\Shader.h"
#include "Assets\Material.h"

#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"

MeshRenderer::MeshRenderer()
{
	m_pShader = nullptr;
	m_pMaterial = nullptr;
	m_pMesh = nullptr;
}

MeshRenderer::~MeshRenderer()
{
	delete m_pMesh;
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Bind()
{
	m_pShader->Bind();
	m_pMaterial->Bind();
	m_pMesh->Bind();
}

void MeshRenderer::Unbind()
{
	m_pMesh->Unbind();
	m_pMaterial->Unbind();
	m_pShader->Unbind();
}

void MeshRenderer::Render(Transform transform, Camera camera, std::vector<Light> lights, int shadowMap, bool setUniforms)
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

		//m_pShader->SetUniform("lights", lights);
		m_pShader->SetUniform("shadowMap", shadowMap);
	}

	Bind();
	m_pMesh->Render();
	Unbind();
}

void MeshRenderer::Render(Light light, bool setUniforms)
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
	m_pMesh->Bind();
	m_pMesh->Render();
	m_pMesh->Unbind();
	shader->Unbind();
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
	m_pMesh = mesh;
}
void MeshRenderer::SetShader(Shader* shader)
{
	m_pShader = shader;
}
void MeshRenderer::SetMaterial(Material* material)
{
	m_pMaterial = material;
}


