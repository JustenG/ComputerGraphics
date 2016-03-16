#pragma once
#include <vector>

class Transform;
class Camera;
class Mesh;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

	void UpdateAllComponents();
	void RenderAllComponents();

	template<typename T>
	int AddComponent();

private:

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
