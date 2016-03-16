#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Assets\Mesh.h"

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::UpdateAllComponents()
{
	for (int i = 0; i < Transfroms.size; ++i)
	{
		Transfroms[i].Update();
	}
}

void ComponentManager::RenderAllComponents()
{
	for (int i = 0; i < Transfroms.size; ++i)
	{
		//Meshs[i].Render();
	}
}

template<>
int ComponentManager::AddComponent<Transform>()
{
	Transfroms.emplace_back();
	return Transfroms.size()-1;
}

//template<>
//int ComponentManager::AddComponent<Camera>()
//{
//	Cameras.emplace_back();
//	return Cameras.size() - 1;
//}