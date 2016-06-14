#include "Components\ComponentManager.h"
#include "Components\ComponentCollection.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Light.h"
#include "Components\MeshRenderer.h"
#include "Components\Terrain.h"
#include "Components\Collider.h"
#include "Components\RigidBody.h"
#include "Components\Particles.h"
#include "Components\PlayerController.h"
#include "Entitys\GameObject.h"
#include "Physics\PhysXManager.h"

ComponentManager* ComponentManager::m_instance = nullptr;

ComponentManager::ComponentManager()
{
	m_physXManager = PhysXManager::GetInstance();

	m_mainCameraIndex = -1;
	m_isFreeCam = false;
	m_isRunning = false;
	m_freeCamPosTransform = nullptr;

	m_pCollectionsMap[typeid(Transform).hash_code()]		= (IComponentCollection*)&m_transforms;
	m_pCollectionsMap[typeid(Camera).hash_code()]			= (IComponentCollection*)&m_cameras;
	m_pCollectionsMap[typeid(Light).hash_code()]			= (IComponentCollection*)&m_lights;
	m_pCollectionsMap[typeid(MeshRenderer).hash_code()]		= (IComponentCollection*)&m_meshRenderers;
	m_pCollectionsMap[typeid(Terrain).hash_code()]			= (IComponentCollection*)&m_terrains;
	m_pCollectionsMap[typeid(Collider).hash_code()]			= (IComponentCollection*)&m_colliders;
	m_pCollectionsMap[typeid(RigidBody).hash_code()]		= (IComponentCollection*)&m_rigidBodys;
	m_pCollectionsMap[typeid(Particles).hash_code()]		= (IComponentCollection*)&m_particles;
	m_pCollectionsMap[typeid(PlayerController).hash_code()]	= (IComponentCollection*)&m_playerControllers;
}

ComponentManager::~ComponentManager()
{
	if (m_freeCamPosTransform != nullptr)
		delete m_freeCamPosTransform;
}

ComponentManager * ComponentManager::GetInstance() 
{
	if (!m_instance)
		m_instance = new ComponentManager();

	return m_instance;
};

Transform* ComponentManager::GetSceneCamTransform()
{
	if (m_freeCamPosTransform == nullptr)
		m_freeCamPosTransform = new Transform();
	return m_freeCamPosTransform;
}

void ComponentManager::SetSceneCamTransform(Transform newTransform)
{
	if (m_freeCamPosTransform == nullptr)
		m_freeCamPosTransform = new Transform();

	m_freeCamPosTransform->SetPosition(newTransform.GetPosition());
	m_freeCamPosTransform->SetRotation(newTransform.GetRotation());
	m_freeCamPosTransform->SetScale(newTransform.GetScale());
}

void ComponentManager::UpdateAllComponents(float deltaTime)
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
		m_cameras[i].Update();
	}
	for (uint i = 0; i < m_lights.Size(); ++i)
	{
		m_lights[i].Update();
	}

	//IF RUNNING
	//----------------------------
	//----------------------------
	if (m_isRunning)
	{
		m_physXManager->Update(deltaTime);
		for (uint i = 0; i < m_colliders.Size(); ++i)
		{
			m_colliders[i].Update();
		}

		for (uint i = 0; i < m_particles.Size(); ++i)
		{
			m_particles[i].Update(deltaTime);
		}

		for (uint i = 0; i < m_playerControllers.Size(); ++i)
		{
			m_playerControllers[i].Update(deltaTime);
		}
	}
	//----------------------------
	//----------------------------

	if (m_mainCameraIndex >= 0)
	{
		if (m_isRunning)
		{
			if (m_isFreeCam)
				m_cameras[m_mainCameraIndex].Update(*GetSceneCamTransform());
		}
		else
		{
			//m_cameras[m_mainCameraIndex].Update(*GetSceneCamTransform());
		}
	}

}

void ComponentManager::RenderAllComponents()
{
	if (m_isRunning)
	{
		for (uint i = 0; i < m_particles.Size(); ++i)
		{
			m_particles[i].Render();
		}
	}

	//Render all Lights
	for (uint i = 0; i < m_lights.Size(); ++i)
	{
		m_lights[i].Bind();
		RenderRenderables(i,true);
		m_lights[i].Unbind();
	}

	//Render all Camera
	for (uint i = 0; i < m_cameras.Size(); ++i)
	{
		m_cameras[i].Bind();
		RenderRenderables(i);
		m_cameras[i].Unbind();
	}
}

void ComponentManager::ToggleRun()
{
	m_isRunning = !m_isRunning;
	if (m_isRunning)
	{
		for (uint i = 0; i < m_colliders.Size(); ++i)
		{
			m_colliders[i].Start();
		}
		for (uint i = 0; i < m_particles.Size(); ++i)
		{
			m_particles[i].Start();
		}
		for (uint i = 0; i < m_playerControllers.Size(); ++i)
		{
			m_playerControllers[i].Start();
		}		
	}
	else
	{
		for (uint i = 0; i < m_particles.Size(); ++i)
		{
			m_particles[i].End();
		}
	}
}

void ComponentManager::RenderRenderables(int camIndex, bool isLight)
{
	//Render all Meshs
	for (uint i = 0; i < m_meshRenderers.Size(); ++i)
	{
		if(isLight)
			m_meshRenderers[i].Render(m_lights[camIndex]);
		else
			m_meshRenderers[i].Render(m_cameras[camIndex], *m_lights.GetContainer(), 0);
	}
	//Render all Terrains
	for (uint i = 0; i < m_terrains.Size(); ++i)
	{
		if(isLight)
			m_terrains[i].Render(m_lights[camIndex]);
		else
			m_terrains[i].Render(m_cameras[camIndex], *m_lights.GetContainer(), 0);
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