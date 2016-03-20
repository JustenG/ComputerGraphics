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

private:

	ComponentManager* m_pComponentManager;

	std::map<size_t, int> m_components;
	template<typename T>
	size_t GetID();

	bool m_hasTransform;
	bool m_hasCamera;
	bool m_hasMesh;
	bool m_hasLight;
};

template<typename T>
void GameObject::AddComponent()
{
	m_components[typeid(T).hash_code()] = ComponentManager->AddComponent<T>();
}

template<typename T>
size_t GameObject::GetID()
{
	return typeid(T).hash_code();
}

