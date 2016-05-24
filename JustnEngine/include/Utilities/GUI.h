#pragma once
#include "global_includes.h"
#include "Utilities\Utils.h"

class EntityManager;
class ComponentManager;
class AssetManager;
class GameObject;
struct GLFWwindow;

class GUI
{
public:
	GUI();
	~GUI();

	void Update();
	void UpdateGizmos();
	void UpdateImGui();
	void Render();

	void Init(GLFWwindow* window, int width, int height);

private:

	void DrawHierarchy();
	void DrawComponents();
	void DrawGameObject(GameObject* object);
	template<typename T>
	void DrawData(T data);

	EntityManager* m_entityManager;
	ComponentManager* m_componentManager;
	AssetManager* m_assetManager;

	std::vector<GameObject*> m_selectedObjects;
	GameObject* m_selectedObject;

	bool m_isImGuiActive;
	bool m_isGizmosActive;

};