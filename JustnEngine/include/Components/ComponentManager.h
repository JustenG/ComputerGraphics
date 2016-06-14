#pragma once
#include "global_includes.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Components\ComponentCollection.h"

class PhysXManager;
class GameObject;
class Transform;
class Camera;
class Light;
class MeshRenderer;
class Terrain;
class Collider;
class RigidBody;
class Particles;
class PlayerController;

template<typename T>
using VT = std::vector<T>;

class ComponentManager
{
public:
	static ComponentManager* GetInstance();
	~ComponentManager();
	ComponentManager(ComponentManager const&) = delete;
	void operator=(ComponentManager const&) = delete;

	Transform* GetSceneCamTransform();
	void SetSceneCamTransform(Transform newTransform);

	void UpdateAllComponents(float deltaTime);
	void RenderAllComponents();

	void ToggleRun();

	//template<typename T>
	//int AddComponent(GameObject* gameObject);
	template<typename T>
	int AddComponent(GameObject* gameObject)
	{
		ComponentCollection<T>* container = (ComponentCollection<T>*)m_pCollectionsMap[typeid(T).hash_code()];

		container->GetContainer()->emplace_back();
		container->Back().Init(gameObject);
		return container->Size() - 1;
	}

	template<typename T>
	T* GetComponent(uint index)
	{
		ComponentCollection<T>* container = (ComponentCollection<T>*)m_pCollectionsMap[typeid(T).hash_code()];
		return &(*container->GetContainer())[index];
	}

	void SetMainCamera(int index);
	Camera* GetMainCamera();
	void SetMainCamResolution(glm::ivec2 resolution) { m_mainCameraResolution = resolution; };

private:

	ComponentManager();
	static ComponentManager* m_instance;

	PhysXManager* m_physXManager;

	int m_mainCameraIndex;
	glm::ivec2 m_mainCameraResolution;

	void RenderRenderables(int camIndex, bool isLight = false);
	bool m_isFreeCam;
	bool m_isRunning;
	Transform* m_freeCamPosTransform;

	//A Vector of every componenet in-game
	ComponentCollection<Transform>				m_transforms;
	ComponentCollection<Camera>					m_cameras;
	ComponentCollection<Light>					m_lights;
	ComponentCollection<MeshRenderer>			m_meshRenderers;
	ComponentCollection<Terrain>				m_terrains;
	ComponentCollection<Collider>				m_colliders;
	ComponentCollection<RigidBody>				m_rigidBodys;
	ComponentCollection<Particles>				m_particles;
	ComponentCollection<PlayerController>		m_playerControllers;

	std::map<uint, IComponentCollection*>	m_pCollectionsMap;

};
