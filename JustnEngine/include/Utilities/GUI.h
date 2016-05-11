#pragma once
#include"global_includes.h"

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

	void PrintObject(GameObject* object);

	EntityManager* m_entityManager;
	ComponentManager* m_componentManager;
	AssetManager* m_assetManager;

	bool m_isImGuiActive;
	bool m_isGizmosActive;

};