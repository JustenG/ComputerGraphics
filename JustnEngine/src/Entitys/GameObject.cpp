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
	m_name				= obj.m_name;

	for (int i = 0; i < obj.m_componentIndex.size(); ++i)
	{
		//init all old components



	}

}

GameObject::~GameObject()
{
}
