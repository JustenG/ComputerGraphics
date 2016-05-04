#pragma once
#include "global_includes.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

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

	template<typename T>
	int AddComponent(GameObject* gameObject);
	template<typename T>
	T* GetComponent(int index);

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
	std::vector<Transform> Transforms;
	std::vector<Transform> TransformsBuffer;
	std::vector<short> ParentIndexBuffer;
	bool m_transformsInline;


	//std::map<T,std::vector<T>> map;
//	std::vector<Camera> Cameras;
//	std::vector<Light> Lights;
//	std::vector<MeshRenderer> MeshRenderers;
//	std::vector<Terrain> Terrains;

	//std::map<uint, ICompenntenColleciton*> m_componentsMap;
	//compnenetMap.add(new vector<Light>())

};

//CompoentnentCollection<T> : ICompenntenColleciton {
//	vector<T>
}