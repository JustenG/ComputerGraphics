#include "Entitys\GameObject.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Assets\Mesh.h"

GameObject::GameObject()
{
	m_pComponentManager = ComponentManager::GetInstance();

	m_hasTransform = false;
	m_hasCamera = false;
}

GameObject::~GameObject()
{
}

template<>
void GameObject::AddComponent<Transform>()
{
	if (m_hasTransform)	return;

	m_hasTransform = true;
	m_componentIndex[typeid(Transform).hash_code()] = m_pComponentManager->AddComponent<Transform>();
}

template<>
void GameObject::AddComponent<Camera>()
{
	if (m_hasCamera || !m_hasTransform) return;

	m_hasCamera = true;
	m_componentIndex[GetID<Camera>()] = m_pComponentManager->AddComponent<Camera>();

	Camera* camera = m_pComponentManager->GetComponent<Camera>(m_componentIndex[GetID<Camera>()]);
	camera->SetTransformIndex(m_componentIndex[GetID<Transform>()]);
}

template<>
void GameObject::AddComponent<Mesh>()
{
	if (m_hasMesh || !m_hasTransform) return;

	m_hasMesh = true;
	m_componentIndex[GetID<Mesh>()] = m_pComponentManager->AddComponent<Mesh>();

	Mesh* mesh = m_pComponentManager->GetComponent<Mesh>(m_componentIndex[GetID<Mesh>()]);
	mesh->SetTransformIndex(m_componentIndex[GetID<Transform>()]);
}

template<>
void GameObject::AddComponent<Light>()
{
	if (m_hasLight || !m_hasTransform) return;

	m_hasLight = true;
	m_componentIndex[GetID<Light>()] = m_pComponentManager->AddComponent<Light>();

	Light* light = m_pComponentManager->GetComponent<Light>(m_componentIndex[GetID<Light>()]);
	light->SetTransformIndex(m_componentIndex[GetID<Transform>()]);
}