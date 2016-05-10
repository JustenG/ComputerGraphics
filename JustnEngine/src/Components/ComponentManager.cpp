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
	m_transformsInline = false;
	m_mainCameraIndex = -1;

	m_collectionsMap[typeid(Transform).hash_code()]		= (IComponentCollection*)&m_transforms;
	m_collectionsMap[typeid(Camera).hash_code()]		= (IComponentCollection*)&m_cameras;
	m_collectionsMap[typeid(Light).hash_code()]			= (IComponentCollection*)&m_lights;
	m_collectionsMap[typeid(MeshRenderer).hash_code()]	= (IComponentCollection*)&m_meshRenderers;
	m_collectionsMap[typeid(Terrain).hash_code()]		= (IComponentCollection*)&m_terrains;


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
	if (!m_transformsInline)
	{
		ReorderTransforms();
	}

	for (uint i = 0; i < m_transforms.Size(); ++i)
	{
		m_transforms[i].Update();
	}
	for (uint i = 0; i < m_transforms.Size(); ++i)
	{
		if (ParentIndexBuffer[i] == -1)
			m_transforms[i].UpdateWorldTransform();
		else
			m_transforms[i].UpdateWorldTransform(m_transforms[ParentIndexBuffer[i]].GetMatrix());
	}

	for (uint i = 0; i < m_cameras.Size(); ++i)
	{
		GameObject* go = m_cameras[i].GetGameObject();
		int index = go->GetComponentIndex<Transform>();
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

void ComponentManager::RequestTransformUpdate()
{
	m_transformsInline = false;
}

void ComponentManager::AddChildren(Transform* parent, short &parentsIndex)
{
	//Add Children To Buffer or Update
	for (size_t i = 0; i < parent->GetChildren().size(); i++)
	{
		TransformsBuffer.GetContainer()->push_back(*parent->GetChildren()[i]);
		ParentIndexBuffer.push_back(parentsIndex);
	}

	for (size_t i = 0; i < parent->GetChildren().size(); i++)
	{
		++parentsIndex;
		if (parent->GetChildren()[i]->GetChildren().size() > 0)
			AddChildren(parent->GetChildren()[i], parentsIndex);
	}
}

void ComponentManager::ReorderTransforms()
{
	short index = 0;
	for (size_t i = 0; i < m_transforms.Size(); ++i)
	{
		if (m_transforms[i].GetParent() == nullptr)
		{
			TransformsBuffer.GetContainer()->push_back(m_transforms[i]);
			ParentIndexBuffer.push_back(-1);
			AddChildren(&m_transforms[i], index);
			++index;
		}
	}
	m_transforms = TransformsBuffer;
	TransformsBuffer.GetContainer()->clear();
	m_transformsInline = true;
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