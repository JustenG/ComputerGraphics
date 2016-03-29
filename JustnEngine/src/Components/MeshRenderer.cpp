#include "Components\MeshRenderer.h"

#include <FBXFile.h>
#include "gl_core_4_4.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "GLFW\glfw3.h"

#include "Assets\Mesh.h"
#include "Assets\Shader.h"
#include "Assets\Material.h"

#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"

#include "Gizmos.h"

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

void MeshRenderer::Render(Transform transform, Camera camera, std::vector<Light> lights, int shadowMap)
{

	m_pShader->SetModelUniform(transform.GetMatrix());

	m_pShader->SetCameraPositionUniform(camera.GetPosition());
	m_pShader->SetProjectionUniform(camera.GetProjection());
	m_pShader->SetViewUniform(camera.GetView());
	m_pShader->SetProjectionViewUniform(camera.GetProjectionView());
	m_pShader->SetProjectionViewModelUniform(camera.GetProjectionView());
	
	m_pShader->SetUniform("specPow", m_specularPower);

	//Only For single light
	//-----------------------------------------------------------------------------------
	// bind the light matrix
	glm::mat4 textureSpaceOffset(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
		);

	glm::mat4 lightMatrix = textureSpaceOffset * lights[0].GetProjectionView();

	auto lightPos = glm::vec3(sin(glfwGetTime()), 1, -sin(glfwGetTime())) * 20;


	Gizmos::addSphere(lightPos, 1.0f, 10, 10, glm::vec4(1));

	const float lightOrthoSize = 12;
	glm::mat4 lightProjection = glm::ortho(-lightOrthoSize, lightOrthoSize, -lightOrthoSize, lightOrthoSize, -lightOrthoSize, lightOrthoSize);
	glm::mat4 lightViewInverse = glm::lookAt(lightPos, glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 textureOffsetTransform(0.5f);
	textureOffsetTransform[3] = glm::vec4(0.5f, 0.5f, 0.5f, 1.f);
	glm::mat4 lightProjectionViewNDC = lightProjection * lightViewInverse;
	glm::mat4 lightProjectionView = textureOffsetTransform * lightProjectionViewNDC;

	m_pShader->SetUniform("lightProjectionView", lightProjectionView);
	m_pShader->SetUniform("lightDir", glm::normalize(glm::vec3(-lights[0].GetWorldTransform()[3])));
	m_pShader->SetUniform("lightColour",glm::vec3(1,1,1));

	//m_pShader->SetUniform("lights", lights);
	//int textureID = (int)lights[0].GetFBO().GetDepthBuffer()->GetID();
	int textureID = 0;
	m_pShader->SetUniform("shadowMap", textureID);
	//-----------------------------------------------------------------------------------

	lights[0].GetFBO().GetDepthBuffer()->Bind();

	Bind();
	m_pMesh->Render();
	Unbind();

	lights[0].GetFBO().GetDepthBuffer()->Unbind();
}

void MeshRenderer::Render(Light light)
{
	Shader* shader = light.GetShader();

	shader->SetProjectionViewUniform(light.GetProjectionView());

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


