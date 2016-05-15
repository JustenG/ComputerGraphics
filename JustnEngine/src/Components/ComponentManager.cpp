#include "Components\ComponentManager.h"
#include "Components\ComponentCollection.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"
#include "Entitys\GameObject.h"

ComponentManager* ComponentManager::m_instance = new ComponentManager();

ComponentManager::ComponentManager()
{
	m_mainCameraIndex = -1;

	m_pCollectionsMap[typeid(Transform).hash_code()]		= (IComponentCollection*)&m_transforms;
	m_pCollectionsMap[typeid(Camera).hash_code()]			= (IComponentCollection*)&m_cameras;
	m_pCollectionsMap[typeid(Light).hash_code()]			= (IComponentCollection*)&m_lights;
	m_pCollectionsMap[typeid(MeshRenderer).hash_code()]		= (IComponentCollection*)&m_meshRenderers;
	m_pCollectionsMap[typeid(Terrain).hash_code()]			= (IComponentCollection*)&m_terrains;
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
	for (uint i = 0; i < m_transforms.Size(); ++i)
	{
		m_transforms[i].Update();
	}
	for (uint i = 0; i < m_transforms.Size(); ++i)
	{
		m_transforms[i].UpdateWorldTransform();
	}

	for (uint i = 0; i < m_cameras.Size(); ++i)
	{
		int index = m_cameras[i].GetGameObject()->GetComponentIndex<Transform>();
		Transform transform = m_transforms[index];
		m_cameras[i].Update(transform);
	}
	for (uint i = 0; i < m_lights.Size(); ++i)
	{
		int index = m_lights[i].GetGameObject()->GetComponentIndex<Transform>();
		Transform transform = m_transforms[index];
		m_lights[i].Update(transform);
	}

}

void ComponentManager::RenderAllComponents()
{
	for (int i = 0; i < (int)m_lights.Size(); ++i)
	{
		m_lights[i].Bind();

		for (int j = 0; j < (int)m_meshRenderers.Size(); ++j)
		{
			int index = m_meshRenderers[i].GetGameObject()->GetComponentIndex<Transform>();
			Transform transform = m_transforms[index];

			m_meshRenderers[j].Render(m_lights[i]);
		}
		for (int j = 0; j < (int)m_terrains.Size(); ++j)
		{
			int index = m_terrains[i].GetGameObject()->GetComponentIndex<Transform>();
			Transform transform = m_transforms[index];

			m_terrains[j].Render(m_lights[i]);
		}
		m_lights[i].Unbind();
	}


	for (int i = 0; i < (int)m_cameras.Size(); ++i)
	{
		m_cameras[i].Bind();

		for (int j = 0; j < (int)m_meshRenderers.Size(); ++j)
		{
			int index = m_meshRenderers[i].GetGameObject()->GetComponentIndex<Transform>();
			Transform transform = m_transforms[index];

			m_meshRenderers[j].Render(m_transforms[index], m_cameras[i], *m_lights.GetContainer(),0);
		}
		for (int j = 0; j < (int)m_terrains.Size(); ++j)
		{
			int index = m_terrains[i].GetGameObject()->GetComponentIndex<Transform>();
			Transform transform = m_transforms[index];

			m_terrains[j].Render(m_transforms[index], m_cameras[i], *m_lights.GetContainer(), 0);
		}
		m_cameras[i].Unbind();
	}
}

void ComponentManager::SetMainCamera(int index)
{
	m_mainCameraIndex = index;
	m_cameras[m_mainCameraIndex].SetResolution(m_mainCameraResolution);
	m_cameras[m_mainCameraIndex].SetToMain();
}

Camera* ComponentManager::GetMainCamera()
{
	if (m_mainCameraIndex == -1)
		return nullptr;
	else
		return &m_cameras[m_mainCameraIndex];
}