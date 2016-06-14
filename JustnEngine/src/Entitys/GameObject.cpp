#include "Entitys\GameObject.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"
#include "Components\Collider.h"
#include "Components\RigidBody.h"
#include "Components\PlayerController.h"

GameObject::GameObject()
{
	m_pComponentManager = ComponentManager::GetInstance();

	m_isStatic = false;
	m_forceStatic = false;
}

GameObject::GameObject(GameObject &obj)
{
	m_pComponentManager = obj.m_pComponentManager;
	m_componentIndex	= obj.m_componentIndex;
	m_name				= obj.m_name;
	m_isStatic			= obj.m_isStatic;
	m_forceStatic		= obj.m_forceStatic;


	if (obj.GetComponent<Transform>()		!= nullptr) GetComponent<Transform>()->Init(this);
	if (obj.GetComponent<Camera>()			!= nullptr) GetComponent<Camera>()->Init(this);
	if (obj.GetComponent<Light>()			!= nullptr) GetComponent<Light>()->Init(this);
	if (obj.GetComponent<MeshRenderer>()	!= nullptr) GetComponent<MeshRenderer>()->Init(this);
	if (obj.GetComponent<Terrain>()			!= nullptr)	GetComponent<Terrain>()->Init(this);
	if (obj.GetComponent<Collider>()		!= nullptr)	GetComponent<Collider>()->Init(this);
	if (obj.GetComponent<RigidBody>()		!= nullptr)	GetComponent<RigidBody>()->Init(this);
	if (obj.GetComponent<PlayerController>()!= nullptr)	GetComponent<PlayerController>()->Init(this);

}

GameObject::~GameObject()
{
}