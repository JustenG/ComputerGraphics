#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Assets\Mesh.h"
#include "Cameras\Camera.h"

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

ComponentManager * ComponentManager::GetInstance() 
{
	if (!m_instance) 
		m_instance = new ComponentManager();

	return m_instance;
};

void ComponentManager::UpdateAllComponents()
{
	for (int i = 0; i < Transfroms.size; ++i)
	{
		Transfroms[i].Update();
	}
	for (int i = 0; i < Cameras.size; ++i)
	{
		int index = Cameras[i].GetTransformIndex();
		Transform transform = Transfroms[index];
		Cameras[i].Update(transform);
	}
	for (int i = 0; i < Lights.size; ++i)
	{
		int index = Lights[i].GetTransformIndex();
		Transform transform = Transfroms[index];
		Lights[i].Update(transform);
	}
	for (int i = 0; i < Meshs.size; ++i)
	{

		for (int i = 0; i < Lights.size; ++i)
		{

			Meshs[i].Update(transform);
		}
	}


}

void ComponentManager::RenderAllComponents()
{
	for (int i = 0; i < Cameras.size; ++i)
	{
		for (int j = 0; j < Meshs.size; ++j)
		{
			int index = Meshs[i].GetTransformIndex();
			Transform transform = Transfroms[index];

			Meshs[j].Render(Transfroms[index],Cameras[i],Lights[i]);
		}
	}
}

template<>
int ComponentManager::AddComponent<Transform>()
{
	Transfroms.emplace_back();
	return Transfroms.size()-1;
}
template<>
Transform* ComponentManager::GetComponent<Transform>(int index)
{
	return &Transfroms[index];
}

template<>
int ComponentManager::AddComponent<Camera>()
{
	Cameras.emplace_back();
	return Cameras.size() - 1;
}
template<>
Camera* ComponentManager::GetComponent<Camera>(int index)
{
	return &Cameras[index];
}