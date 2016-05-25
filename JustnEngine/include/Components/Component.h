#pragma once
#include "global_includes.h"
#include "Components\BaseComponent.h"
#include <tuple>
#include "Utilities\Utils.h"

class GameObject;

template <class... TRequirements>
class Component : public BaseComponent
{
public:
	Component() {};
	~Component() {};

	static bool CheckRequirements(GameObject* gameObject);

	virtual BaseData* ToData() {};
	virtual void FromData(BaseData* newData) {};
};

template <class... TRequirements>
bool Component<TRequirements...>::CheckRequirements(GameObject* gameObject)
{
	for( auto& req : Utils::GetTypes<TRequirements...>() )
	{
		if (!gameObject->HasComponent(req))
		{
			return false;
		}
	}
	return true;
}


