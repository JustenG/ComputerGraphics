#include "Application.h"

#include "Cameras/FlyCamera.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "Components\ComponentManager.h"
Application::Application()
{
}

int Application::Startup(int width, int height)
{
	//Setup Data
	currentTime = 0;
	deltaTime = 0;
	previousTime = (float)glfwGetTime();
	white = vec4(0, 0, 0, 1);
	black = vec4(1, 1, 1, 1);
	m_isGizmosActive = false;
	m_pCamera = nullptr;

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
	//Initialise GUI
	ImGui_ImplGlfwGL3_Init(m_pWindow, true);

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = width;
	io.DisplaySize.y = height;

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
	UpdateGL();
	if(m_isGizmosActive) UpdateGizmos();
	UpdateImGui();
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
void Application::UpdateGL()
{
	//OPEN GL settings
	//---------------------------------------------------------

	//---------------------------------------------------------
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
	ImGui::ColorEdit3("Grid Colour", glm::value_ptr(white));
}

 void Application::Render()
 {
	 if (m_pCamera == nullptr) 
	 { 
		 printf("WARNING: No camera set, unable to render"); 
		 return; 
	 }

	 Draw();
	 if(m_isGizmosActive) DrawGizmos();
	 ImGui::Render();
 }

void Application::DrawGizmos()
{
	if(m_pCamera != nullptr) Gizmos::draw(m_pCamera->GetProjectionView());
}

void Application::Shutdown()
{
	Gizmos::destroy();
	ImGui_ImplGlfwGL3_Shutdown();
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
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
	m_pCamera = camera;
}

void Application::SetGizmos(bool active)
{
	m_isGizmosActive = active;
}


