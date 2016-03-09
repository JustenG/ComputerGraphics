#include "Application.h"

#include "Cameras/FlyCamera.h"

Application::Application()
{
}


Application::~Application()
{
}

Camera* Application::GetCamera()
{
	return m_fCamera;
}

int Application::Startup()
{
	currentTime = 0;
	deltaTime = 0;
	previousTime = (float)glfwGetTime();
	m_fCamera = new FlyCamera();
	white = vec4(0, 0, 0, 1);
	black = vec4(1, 1, 1, 1);

	//If GL fails to initalise
	if (glfwInit() == false)
		return -1;

	//Make window
	window = glfwCreateWindow(1280, 720, "Open GL - Computer Graphics", nullptr, nullptr);

	//If window fails
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	//If window fails to remap all of OpenGL’s function calls to the correct versions and feature sets
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	
	Gizmos::create();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	major = ogl_GetMajorVersion();
	minor = ogl_GetMinorVersion();

	camRotation = 0;
	camX = 200;
	camY = 200;

	return 0;
}

void Application::Run()
{
	Startup();

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//RunEvents(); // (Virtual fucntion)
		EarlyUpdate();
		Update();
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Shutdown();
}


void Application::EarlyUpdate()
{
	//Time
	//-------------------------------------------------------------------
	currentTime = (float)glfwGetTime();
	deltaTime = currentTime - previousTime; // prev of last frame
	previousTime = currentTime;
	//-------------------------------------------------------------------

	//OPEN GL settings
	//---------------------------------------------------------
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//---------------------------------------------------------

	//Update Camera
	//------------------------------
	m_fCamera->Update(deltaTime, window);
	//------------------------------

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
void Application::DrawGizmos()
{
	Gizmos::draw(m_fCamera->GetProjectionView());
}
void Application::Shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();

	delete m_fCamera;
}

