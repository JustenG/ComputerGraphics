#pragma once
#include "global_includes.h"
#include "Components\ComponentManager.h"
#include "Components\BaseComponent.h"
#include "Components\Terrain.h"
#include "Utilities\Utils.h"
#include <type_traits>

class GameObject
{
public:
	GameObject();
	GameObject(GameObject &obj);  // copy constructor
	~GameObject();

	//Add a component to Game Object
	template<class T>
	typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type
	AddComponent();

	//Get a component to Game Object
	template<class T>
	T* GetComponent();

	//Get a components index into Component Managers Componenet Collections
	template<typename T>
	int GetComponentIndex();

	//Get a components index into Component Managers Componenet Collections
	template<typename T>
	bool HasComponent();
	bool HasComponent(uint hashCode)
	{
		if (m_componentIndex.find(hashCode) != m_componentIndex.end())
			return true;

		return false;
	}

	uint GetComponentCount() { return m_componentIndex.size(); };
	void SetName(std::string name) {  m_name = name; };
	std::string GetName() { return m_name; };
	bool GetStaticTag() { return m_isStatic; };

private:

	ComponentManager* m_pComponentManager;
	std::map<uint, int> m_componentIndex;
	std::string m_name;
	bool m_isStatic;
	bool m_forceStatic;
};

template<class TComponent>
typename std::enable_if<std::is_base_of<BaseComponent, TComponent>::value>::type
GameObject::AddComponent()
{
	if (!TComponent::CheckRequirements(this))
		return;

	//Already has this component
	if (HasComponent<TComponent>())
		return;

	if (Utils::IsSameType<TComponent, Terrain>())
	{
		m_isStatic = true;
		m_forceStatic = true;
	}

	m_componentIndex[Utils::GetTypeID<TComponent>()] = m_pComponentManager->AddComponent<TComponent>(this);
}

template<class TComponent>
TComponent* GameObject::GetComponent()
{
	if (GetComponentIndex<TComponent>() >= 0)
		return m_pComponentManager->GetComponent<TComponent>(GetComponentIndex<TComponent>());
	else
		return nullptr;
}

template<typename TComponent>
int GameObject::GetComponentIndex()
{
	if (m_componentIndex.find(Utils::GetTypeID<TComponent>()) != m_componentIndex.end())
		return m_componentIndex[Utils::GetTypeID<TComponent>()];
	else
		return -1;
}

template<typename TComponent>
bool GameObject::HasComponent()
{
	if (m_componentIndex.find(Utils::GetTypeID<TComponent>()) != m_componentIndex.end())
		return true;

	return false;
}
