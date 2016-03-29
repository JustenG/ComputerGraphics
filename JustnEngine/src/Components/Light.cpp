#include "Components\Light.h"
#include "Assets\AssetManager.h"

#include "Components\Transform.h"

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

void Light::Update(Transform transform)
{
	//glm::vec3 forward = transform.GetMatrix()[3];
	//forward = glm::normalize(forward);
	worldTransform = transform.GetMatrix();
	UpdateLightProjectionViewTransform();
}

void Light::UpdateLightProjectionViewTransform()
{
	glm::mat4 lightView = glm::lookAt(GetPosition(), glm::vec3(0), glm::vec3(0, 1, 0));
	projectionViewTransform = GetProjection() * lightView;
}
