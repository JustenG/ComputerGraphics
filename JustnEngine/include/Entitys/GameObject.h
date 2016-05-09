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

	template<class T>
	typename std::enable_if<std::is_base_of<BaseComponent, T>::value>::type
	AddComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	int GetComponentIndex();

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
	std::map<size_t, int> m_componentIndex;
	std::string m_name;
};

template<class TComponent>
typename std::enable_if<std::is_base_of<BaseComponent, TComponent>::value>::type
GameObject::AddComponent()
{
	if (!TComponent::CheckRequirements(this))
		return;

	if (HasComponent<TComponent>())
	{
		//Already has this component
		if (TComponent::IsSingular()) return;
	}

	m_componentIndex[GetTypeID<TComponent>()] = m_pComponentManager->AddComponent<TComponent>(this);
}

template<typename TComponent>
TComponent* GameObject::GetComponent()
{
	return m_pComponentManager->GetComponent<TComponent>(m_componentIndex[GetTypeID<TComponent>()]);
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

