#pragma once

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;


class FlyCamera;
class Asset;

class Application
{
public:
	Application();
	virtual ~Application();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	int Startup();
	void Run();
	void EarlyUpdate();
	void DrawGizmos();
	void Shutdown();

private:
	
	//WINDOW
	//------------------------
	GLFWwindow* window;
	//------------------------

	//TIME
	//-----------------------
	float currentTime;
	float deltaTime;
	float previousTime;
	//-----------------------

	//Version Control
	//------------------------
	int major;
	int minor;
	//------------------------

	//Camera
	//------------------------
	FlyCamera* m_fCamera;

	float camRotation;
	float camX;
	float camY;
	//-----------------------

	vec4 white;
	vec4 black;

	Asset* m_Soulspear;
	Asset* m_Pyro;

};

