#pragma once

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define GUI ImGui
using glm::vec3;
using glm::vec4;
using glm::mat4;

class FlyCamera;
class Camera;
class Asset;
class EntityManager;
class ComponentManager;
class AssetManager;

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
	void UpdateGL();
	void UpdateGizmos();
	void UpdateImGui();
	void Render();
	void DrawGizmos();
	void Shutdown();

	void SetCamera(Camera* camera);
	void SetGizmos(bool active);

	EntityManager* GetEntityManager();
	ComponentManager* GetComponentManager();
	AssetManager* GetAssetManager();

	float GetDeltaTime();
	GLFWwindow* GetWindow();

private:
	
	//WINDOW
	//------------------------
	GLFWwindow* m_pWindow;
	GLuint* m_fbo;
	//------------------------

	EntityManager* m_entityManager;
	ComponentManager* m_componentManager;
	AssetManager* m_assetManager;

	//TIME
	//-----------------------
	float currentTime, deltaTime, previousTime;
	//-----------------------

	bool m_isGizmosActive;
	bool m_isGUIActive;

	vec4 white, black;
};

