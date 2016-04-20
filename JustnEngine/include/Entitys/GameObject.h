#pragma once
#include "global_includes.h"
#include "Components\ComponentManager.h"
#include "Components\Component.h"

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

template<class TComponent>
void GameObject::AddComponent()
{
	if (!TComponent::CheckRequirements(this))
		return;

	if (m_componentIndex.find(GetTypeID<TComponent>()) != m_componentIndex.end())
	{
		//Already has this component
		if (TComponent::IsSingular()) return;
	}

	m_componentIndex[GetTypeID<TComponent>()] = m_pComponentManager->AddComponent<TComponent>(this);
}

template<class TComponent>
T* GameObject::GetComponent()
{
	return m_pComponentManager->GetComponent<TComponent>(m_componentIndex[GetTypeID<TComponent>()]);
}

template<class TComponent>
int GameObject::GetComponentIndex()
{
	return m_componentIndex[GetTypeID<TComponent>()];
}


template<typename T>
size_t GameObject::GetTypeID()
{
	return typeid(T).hash_code();
}

