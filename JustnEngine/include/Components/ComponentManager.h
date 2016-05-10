#pragma once
#include "global_includes.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <unordered_map>
#include "Components\ComponentCollection.h"

class GameObject;
class Transform;
class Camera;
class Light;
class MeshRenderer;
class Terrain;

template<typename T>
using VT = std::vector<T>;

class ComponentManager
{
public:
	static ComponentManager* GetInstance();
	~ComponentManager();
	ComponentManager(ComponentManager const&) = delete;
	void operator=(ComponentManager const&) = delete;

	void UpdateAllComponents();
	void RenderAllComponents();

	//template<typename T>
	//int AddComponent(GameObject* gameObject);
	template<typename T>
	int AddComponent(GameObject* gameObject)
	{
		ComponentCollection<T>* container = (ComponentCollection<T>*)m_collectionsMap[typeid(T).hash_code()];

		container->GetContainer()->emplace_back();
		container->Back().Init(gameObject);
		return container->Size() - 1;
	}

	template<typename T>
	T* GetComponent(int index)
	{
		ComponentCollection<T>* container = (ComponentCollection<T>*)m_collectionsMap[typeid(T).hash_code()];
		return &(*container->GetContainer())[index];
	}

	void SetMainCamera(int index);
	Camera* GetMainCamera();
	void SetMainCamResolution(glm::ivec2 resolution) { m_mainCameraResolution = resolution; };

	void RequestTransformUpdate();

private:

	void AddChildren(Transform* parent, short &parentsIndex);
	void ReorderTransforms();

	ComponentManager();
	static ComponentManager* m_instance;

	int m_mainCameraIndex;
	glm::ivec2 m_mainCameraResolution;

	//A Vector of every componenet in-game
	ComponentCollection<Transform> m_transforms;
	ComponentCollection<Transform> TransformsBuffer;
	std::vector<short> ParentIndexBuffer;
	bool m_transformsInline;


	//std::map<T,std::vector<T>> map; 
	ComponentCollection<Camera>			m_cameras;
	ComponentCollection<Light>			m_lights;
	ComponentCollection<MeshRenderer>	m_meshRenderers;
	ComponentCollection<Terrain>		m_terrains;

	std::map<int, IComponentCollection*> m_collectionsMap;

};
