#pragma once
#include "global_includes.h"
class GameObject;

//TODO 
//Move TO Utils.h
template <typename... TArgs>
std::vector<size_t> GetTypes();

template <typename... TArgs>
std::vector<size_t> GetTypes()
{
	vector<size_t> result = { typeid(TArgs).hash_code()... };
	return result;
}

template <class... TRequirements>
class Component
{
public:
	Component();
	//Component(GameObject* gameObject);
	~Component();

	virtual void Update() = 0;

	void SetTransformIndex(int transformIndex);
	int GetTransformIndex();

	GameObject* GetGameObject() { return m_gameObject; };

private:

	GameObject* m_gameObject;

	std::vector<size_t> requirements;
	int m_transformIndex;

};

template <class... TRequirements>
Component<TRequirements>::Component()
{
	requirements = GetTypes<TRequirements>();
}

template <class... TRequirements>
Component<TRequirements>::Component(GameObject* gameObject)
{
	m_gameObject = gameObject;
	requirements = GetTypes<TRequirements>();
}

template <class... TRequirements>
Component<TRequirements>::~Component()
{
	
}

template <class... TRequirements>
void Component<TRequirements>::SetTransformIndex(int transformIndex)
{
	m_transformIndex = transformIndex;
}

template <class... TRequirements>
int Component<TRequirements>::GetTransformIndex()
{
	return m_transformIndex;
}
