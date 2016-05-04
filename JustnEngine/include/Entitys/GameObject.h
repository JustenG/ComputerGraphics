#pragma once
#include "global_includes.h"
#include "Components\ComponentManager.h"
#include "Components\Component.h"

#include <type_traits>


class GameObject
{
public:
	GameObject();
	~GameObject();

	template<typename T>
	void AddComponent();

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

	std::string GetName() { return m_name; };

private:

	ComponentManager* m_pComponentManager;

	std::map<size_t, int> m_componentIndex;
	template<typename T>
	size_t GetTypeID();

	std::string m_name;

	bool m_hasTransform;
	bool m_hasCamera;
	bool m_hasMesh;
	bool m_hasLight;
};

//typename std::enable_if<std::is_base_of<Component<>, TComponent>::value,bool>::type
template<typename TComponent> 
void GameObject::AddComponent()
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

