#include "Application.h"

#include "Components\ComponentManager.h"
#include "Entitys\EntityManager.h"
#include "Assets\AssetManager.h"

#include "Components\Transform.h"
#include "Utilities\GUI.h"

#include "Components\Camera.h"

#include "all_includes.h"

Application::Application()
{
}

Application::~Application()
{
}

int Application::Startup(int width, int height)
{
	m_entityManager = EntityManager::GetInstance();
	m_componentManager = ComponentManager::GetInstance();
	m_assetManager = AssetManager::GetInstance();

	//Setup Data
	currentTime = 0;
	deltaTime = 0;
	previousTime = (float)glfwGetTime();
	m_isGUIActive = true;

	m_componentManager->SetMainCamResolution(ivec2(width, height));

	//If GL fails to initalise
	if (glfwInit() == false)
		return -1;

	//Make window
	m_pWindow = glfwCreateWindow(width, height, "Open GL - Computer Graphics", nullptr, nullptr);

	//If window fails
	if (m_pWindow == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(m_pWindow);

	//If window fails to remap all of OpenGL’s function calls to the correct versions and feature sets
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_pWindow);
		glfwTerminate();
		return -3;
	}

	//SetUp GL input
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//Activate GUI is on
	if (m_isGUIActive)
	{
		m_GUI = new GUI();
		m_GUI->Init(m_pWindow, width, height);
	}

	glEnable(GL_DEPTH_TEST);

	return 0;
}

void Application::Run(int windowWidth, int windowHeight)
{
	if (Startup(windowWidth, windowHeight) != 0) return;
	Initialise();

	while (glfwWindowShouldClose(m_pWindow) == false && glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		EngineUpdate();
		EarlyUpdate();
		Update();
		LateUpdate();

		Render();

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}

	Destroy();
	Shutdown();
}

void Application::EngineUpdate()
{
	UpdateTime();
	m_componentManager->UpdateAllComponents(deltaTime);
	if(m_isGUIActive) m_GUI->Update();
}

void Application::UpdateTime()
{
	//Time
	//-------------------------------------------------------------------
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - previousTime; // prev of last frame
	previousTime = currentTime;
	//-------------------------------------------------------------------
}

 void Application::Render()
 {
	 if (m_componentManager->GetMainCamera() == nullptr)
	 {
		 printf("WARNING: No camera set, unable to render \n"); 
	 }

	 m_componentManager->RenderAllComponents();
	 if(m_isGUIActive) m_GUI->Render();
 }

void Application::Shutdown()
{
	if (m_isGUIActive)	delete m_GUI;
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

EntityManager* Application::GetEntityManager()
{
	return m_entityManager;
}
ComponentManager* Application::GetComponentManager()
{
	return m_componentManager;
}
AssetManager* Application::GetAssetManager()
{
	return m_assetManager;
}

float Application::GetDeltaTime()
{
	return deltaTime;
}

GLFWwindow* Application::GetWindow()
{
	return m_pWindow;
}

void Application::SetGUI(bool active)
{
	m_isGUIActive = active;
}


