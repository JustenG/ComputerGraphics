#include "Entitys\GameObject.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"

GameObject::GameObject()
{
	m_pComponentManager = ComponentManager::GetInstance();

	m_hasTransform = false;
	m_hasCamera = false;
	m_hasMesh = false;
	m_hasLight = false;
}

GameObject::~GameObject()
{
}