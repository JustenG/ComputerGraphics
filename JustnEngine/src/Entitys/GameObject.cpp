#include "Entitys\GameObject.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"

GameObject::GameObject()
{
	m_pComponentManager = ComponentManager::GetInstance();
}

GameObject::GameObject(GameObject &obj)
{
	m_pComponentManager = obj.m_pComponentManager;
	m_componentIndex	= obj.m_componentIndex;
	m_name				= obj.m_name;

	if (obj.GetComponent<Transform>()		!= nullptr) GetComponent<Transform>()->Init(this);
	if (obj.GetComponent<Camera>()			!= nullptr) GetComponent<Camera>()->Init(this);
	if (obj.GetComponent<Light>()			!= nullptr) GetComponent<Light>()->Init(this);
	if (obj.GetComponent<MeshRenderer>()	!= nullptr) GetComponent<MeshRenderer>()->Init(this);
	if (obj.GetComponent<Terrain>()			!= nullptr)	GetComponent<Terrain>()->Init(this);

}

GameObject::~GameObject()
{
}