#include "Application.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "Components\ComponentManager.h"
#include "Entitys\EntityManager.h"
#include "Assets\AssetManager.h"
#include "Components\Transform.h"
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
	white = vec4(0, 0, 0, 1);
	black = vec4(1, 1, 1, 1);
	m_isGizmosActive = true;
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
	
	if (m_isGUIActive)
	{
		//Initialise GUI
		ImGui_ImplGlfwGL3_Init(m_pWindow, true);

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = (float)width;
		io.DisplaySize.y = (float)height;
	}
	//Create Gizmos
	Gizmos::create();

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
	m_componentManager->UpdateAllComponents();
	if(m_isGizmosActive) UpdateGizmos();
	if(m_isGUIActive) UpdateImGui();
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

void Application::UpdateGizmos()
{
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	//Draw Grid
	//----------------------------------------------------
	int gridScale = 5;
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10) * gridScale, vec3(-10 + i, 0, -10) * gridScale, i == 10 * gridScale ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i) * gridScale, vec3(-10, 0, -10 + i) * gridScale, i == 10 * gridScale ? white : black);
	}
	//----------------------------------------------------
}

void Application::UpdateImGui()
{
	//Clear ImGui
	ImGui_ImplGlfwGL3_NewFrame();

	//Update ImGuiS
	GUI::Begin("GameObjects");
	for (int i = 0; i < GetEntityManager()->GetEntityCount(); ++i)
	{
		GameObject* object = &(GetEntityManager()->GetEntitys()->data())[i];
		PrintObject(object);
	}
	GUI::End();
}

void Application::PrintObject(GameObject* object)
{
	std::string name(object->GetName());

	Transform* parent = object->GetComponent<Transform>();

	if(GUI::TreeNode(name.c_str()))
	{
		if (parent->GetChildren().size() > 0)
		{
			for (int i = 0; i < parent->GetChildren().size(); ++i)
			{
				GameObject* child = parent->GetChildren()[i]->GetGameObject();
				PrintObject(child);
			}
		}
		GUI::TreePop();
	}
	return;
}


 void Application::Render()
 {
	/* if (m_pCamera == nullptr) 
	 { 
		 printf("WARNING: No camera set, unable to render"); 
		 return; 
	 }*/

	 m_componentManager->RenderAllComponents();
	 if(m_isGizmosActive) DrawGizmos();
	 if(m_isGUIActive) ImGui::Render();

 }

void Application::DrawGizmos()
{
	if (m_componentManager->GetMainCamera() != nullptr)
	{
		mat4 projectionView = m_componentManager->GetMainCamera()->GetProjectionView();
		Gizmos::draw(projectionView);
	}
}

void Application::Shutdown()
{
	Gizmos::destroy();
	ImGui_ImplGlfwGL3_Shutdown();
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

void Application::SetCamera(Camera* camera)
{
	//m_pCamera = camera;
}

void Application::SetGizmos(bool active)
{
	m_isGizmosActive = active;
}


