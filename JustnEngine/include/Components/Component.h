#pragma once
#include "global_includes.h"
#include "Components\BaseComponent.h"
#include <tuple>
class GameObject;

//TODO 
//Move TO Utils.h
//-----------------------------
template <typename... TArgs>
std::vector<size_t> GetTypes()
{
	std::vector<size_t> result = { typeid(TArgs).hash_code()... };
	return result;
}
//-----------------------------

template <class... TRequirements>
class Component : public BaseComponent
{
public:
	Component() {};
	~Component() {};

	static bool CheckRequirements(GameObject* gameObject);
};

template <class... TRequirements>
bool Component<TRequirements...>::CheckRequirements(GameObject* gameObject)
{
	for( auto& req : GetTypes<TRequirements...>() )
	{
		if (!gameObject->HasComponent(req))
		{
			return false;
		}
	}
	return true;
}


