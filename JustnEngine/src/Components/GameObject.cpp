#include "Components\GameObject.h"
#include "Components\Transform.h"
#include "Cameras\Camera.h"
//#include "Components\Light.h"

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
	m_components[typeid(Transform).hash_code()] = m_pComponentManager->AddComponent<Transform>();
}

template<>
void GameObject::AddComponent<Camera>()
{
	if (m_hasCamera || !m_hasTransform) return;

	m_hasCamera = true;
	m_components[GetID<Camera>()] = m_pComponentManager->AddComponent<Camera>();

	Camera* camera = m_pComponentManager->GetComponent<Camera>(m_components[GetID<Camera>()]);
	Transform* transform = m_pComponentManager->GetComponent<Transform>(m_components[GetID<Camera>()]);
	camera->SetTransformIndex(m_components[GetID<Camera>()]);
}

template<>
void GameObject::AddComponent<Mesh>()
{
	if (m_hasMesh || !m_hasTransform) return;

	m_hasMesh = true;
	m_components[GetID<Mesh>()] = m_pComponentManager->AddComponent<Mesh>();

	Mesh* camera = m_pComponentManager->GetComponent<Mesh>(m_components[GetID<Mesh>()]);
	Transform* transform = m_pComponentManager->GetComponent<Transform>(m_components[GetID<Mesh>()]);
	camera->SetTransformIndex(m_components[GetID<Mesh>()]);
}

//template<>
//void GameObject::AddComponent<Light>()
//{
//	if (m_hasLight || !m_hasTransform) return;
//
//	m_hasLight = true;
//	m_components[GetID<Light>()] = m_pComponentManager->AddComponent<Light>();
//
//	Light* camera = m_pComponentManager->GetComponent<Light>(m_components[GetID<Light>()]);
//	Transform* transform = m_pComponentManager->GetComponent<Transform>(m_components[GetID<Light>()]);
//	camera->SetTransformIndex(m_components[GetID<Light>()]);
//}