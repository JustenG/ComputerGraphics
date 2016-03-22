#pragma once
#include <vector>

class Transform;
class Camera;
class Mesh;

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
	int AddComponent();
	template<typename T>
	T* GetComponent(int index);

	void SetMainCamera(int index);

private:
	ComponentManager();
	static ComponentManager* m_instance;

	int m_mainCameraIndex;

	//A Vector of every componenet in-game
	std::vector<Transform> Transfroms;
	std::vector<Camera> Cameras;
	std::vector<Mesh> Meshs;

};

//template<typename T>
//int ComponentManager::AddComponent<T>()
//{
//	if (T != anyComponenet)
//		//Print Error
//}
