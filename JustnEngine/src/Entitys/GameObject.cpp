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
void GameObject::AddComponent<MeshRenderer>()
{
	if (m_hasMesh || !m_hasTransform) return;

	m_hasMesh = true;
	m_componentIndex[GetID<MeshRenderer>()] = m_pComponentManager->AddComponent<MeshRenderer>();

	MeshRenderer* mesh = m_pComponentManager->GetComponent<MeshRenderer>(m_componentIndex[GetID<MeshRenderer>()]);
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

template<>
void GameObject::AddComponent<Terrain>()
{
	if (!m_hasTransform) return;

	m_componentIndex[GetID<Terrain>()] = m_pComponentManager->AddComponent<Terrain>();

	Terrain* terrain = m_pComponentManager->GetComponent<Terrain>(m_componentIndex[GetID<Terrain>()]);
	terrain->SetTransformIndex(m_componentIndex[GetID<Transform>()]);
}