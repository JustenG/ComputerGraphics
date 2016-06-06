#include "Components\Light.h"
#include "Assets\AssetManager.h"

#include "Components\Transform.h"
#include "Entitys\GameObject.h"

using glm::mat4;
using glm::mat3;
using glm::vec4;
using glm::vec3;
using glm::vec2;

Light::Light() : Camera()
{
	SetToLight();
	if (AssetManager::GetInstance()->GetAsset<Shader>("depth") == nullptr)
	{
		AssetManager::GetInstance()->LoadShader("data/shaders/depth.vert", "data/shaders/depth.frag","depth");
		m_FBO.SetShaderProgram(AssetManager::GetInstance()->GetAsset<Shader>("depth"));
	}
	else
	{
		m_FBO.SetShaderProgram(AssetManager::GetInstance()->GetAsset<Shader>("depth"));
	}

}

Light::~Light()
{

}

void Light::Update()
{
	//glm::vec3 forward = transform.GetMatrix()[3];
	//forward = glm::normalize(forward);

	worldTransform = GetGameObject()->GetComponent<Transform>()->GetMatrix();
	UpdateLightProjectionViewTransform();
}

void Light::UpdateLightProjectionViewTransform()
{
	//glm::mat4 lightView = glm::lookAt(GetPosition(), glm::vec3(0), glm::vec3(0, 1, 0));
	projectionViewTransform = GetProjection() * GetLightView();
}

mat4 Light::GetLightView()
{
	return worldTransform * glm::lookAt(GetPosition(), vec3(0), vec3(0, 1, 0));
}
