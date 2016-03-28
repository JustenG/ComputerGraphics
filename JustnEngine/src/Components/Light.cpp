#include "Components\Light.h"
#include "Assets\AssetManager.h"

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
