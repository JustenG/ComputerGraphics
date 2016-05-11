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

GameObject::GameObject(const GameObject &obj)
{
	m_pComponentManager = obj.m_pComponentManager;
	m_componentIndex	= obj.m_componentIndex;
	m_pComponents		= obj.m_pComponents;
	m_name				= obj.m_name;


	for (std::map<uint, BaseComponent*>::iterator i = m_pComponents.begin(); i != m_pComponents.end(); ++i)
	{
		//init all old components
		i->second->Init(this);
	}
}

GameObject::~GameObject()
{
}