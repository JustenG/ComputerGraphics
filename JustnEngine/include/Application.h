#pragma once

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include"global_includes.h"

class EntityManager;
class ComponentManager;
class AssetManager;

class Camera;
class GUI;

class Application
{
public:
	Application();
	virtual ~Application();

	virtual void Initialise() = 0;
	virtual void EarlyUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	int Startup(int width, int height);
	void Run(int windowWidth, int windowHeight);
	void EngineUpdate();
	void UpdateTime();
	void Render();
	void Shutdown();

	void SetGUI(bool active);

	EntityManager* GetEntityManager();
	ComponentManager* GetComponentManager();
	AssetManager* GetAssetManager();

	float GetDeltaTime();
	GLFWwindow* GetWindow();

private:
	
	//WINDOW
	//------------------------
	GLFWwindow* m_pWindow;
	uint* m_fbo;
	//------------------------

	EntityManager* m_entityManager;
	ComponentManager* m_componentManager;
	AssetManager* m_assetManager;
	GUI* m_GUI;

	//TIME
	//-----------------------
	float currentTime, deltaTime, previousTime;
	//-----------------------

	bool m_isGUIActive;
};

