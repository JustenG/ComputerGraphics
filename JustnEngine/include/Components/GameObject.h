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

	std::map<char const*, int> Components;
};

template<typename T>
void GameObject::AddComponent()
{
	Components[typeid(T).name()] = ComponentManager->AddComponent<T>();
}

