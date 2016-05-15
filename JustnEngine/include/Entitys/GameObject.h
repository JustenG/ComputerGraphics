#pragma once
#include "global_includes.h"
#include "Components\ComponentManager.h"
#include "Components\BaseComponent.h"

#include <type_traits>


class GameObject
{
public:
	GameObject();
	GameObject(const GameObject &obj);  // copy constructor
	~GameObject();

	//Add a component to Game Object
	template<class T>
	typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type
	AddComponent();

	//Get a component to Game Object
	template<typename T>
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

private:

	template<typename T>
	size_t GetTypeID();

	ComponentManager* m_pComponentManager;
	std::map<uint, int> m_componentIndex;
	std::string m_name;
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

	m_componentIndex[GetTypeID<TComponent>()] = m_pComponentManager->AddComponent<TComponent>(this);
}

template<typename TComponent>
TComponent* GameObject::GetComponent()
{
	return m_pComponentManager->GetComponent<TComponent>(GetComponentIndex<TComponent>());
}

template<typename TComponent>
int GameObject::GetComponentIndex()
{
	return m_componentIndex[GetTypeID<TComponent>()];
}

template<typename TComponent>
bool GameObject::HasComponent()
{
	if (m_componentIndex.find(GetTypeID<TComponent>()) != m_componentIndex.end())
		return true;

	return false;
}

template<typename T>
size_t GameObject::GetTypeID()
{
	return typeid(T).hash_code();
}

