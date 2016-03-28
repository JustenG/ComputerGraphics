#pragma once
#include <map>
#include <typeinfo>
#include "Components\ComponentManager.h"

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

	template<typename T>
	void AddComponent();
	template<typename T>
	T* GetComponent();

private:

	ComponentManager* m_pComponentManager;

	std::map<size_t, int> m_componentIndex;
	template<typename T>
	size_t GetID();

	bool m_hasTransform;
	bool m_hasCamera;
	bool m_hasMesh;
	bool m_hasLight;
};

template<typename T>
T* GameObject::GetComponent()
{
	return m_pComponentManager->GetComponent<T>(m_componentIndex[GetID<T>()]);
}

template<typename T>
size_t GameObject::GetID()
{
	return typeid(T).hash_code();
}

