#include "Cameras/FlyCamera.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;


FlyCamera::FlyCamera()
{
	SetSpeed(5);
	SetPerspective(45, 16 / 9.0f, 1, 1000);
	SetLookAt(vec3(0,10,10), vec3(0), vec3(0, 1, 0));

	prevMouseX = 0;
	prevMouseY = 0;
}


FlyCamera::~FlyCamera()
{

}

void FlyCamera::Update(float deltaTime, GLFWwindow* window)
{
	GetInput(deltaTime, window);
	MouseContol(deltaTime, window);
	UpdateProjectionViewTransform();
}
void FlyCamera::SetSpeed(float _speed)
{
	speed = _speed;
}

void FlyCamera::GetInput(float deltaTime, GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vec3 vForward = glm::normalize( vec3(worldTransform[2].x, worldTransform[2].y, worldTransform[2].z) );
		MovePos(-vForward * speed * deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vec3 vForward = glm::normalize( vec3(worldTransform[2].x, worldTransform[2].y, worldTransform[2].z) );
		MovePos(vForward * speed * deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3 vRight = vec3(worldTransform[0].x, worldTransform[0].y, worldTransform[0].z);
		MovePos(-vRight * speed * deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3 vRight = vec3(worldTransform[0].x, worldTransform[0].y, worldTransform[0].z);
		MovePos(vRight * speed * deltaTime);
	}
}

void FlyCamera::MouseContol(float deltaTime, GLFWwindow* window)
{
	double x = 0, y = 0;

	glfwGetCursorPos(window, &x, &y);

	if (prevMouseX == 0 && prevMouseY == 0)
	{
		prevMouseX = x;
		prevMouseY = y;
	}
	else
	{
		int movmentX = prevMouseX - (int)x;
		int movmentY = prevMouseY - (int)y;

		prevMouseX = x;
		prevMouseY = y;

		if (movmentX != 0.0f)
		{
			glm::mat4 rotMat = glm::axisAngleMatrix(vec3(0, 1, 0), movmentX * 0.005f);
			worldTransform[0] = rotMat * worldTransform[0];
			worldTransform[1] = rotMat * worldTransform[1];
			worldTransform[2] = rotMat * worldTransform[2];
		}
		if (movmentY != 0.0f)
		{
			glm::mat4 rotMat = glm::axisAngleMatrix(vec3(worldTransform[0]), movmentY * 0.005f);
			worldTransform[0] = rotMat * worldTransform[0];
			worldTransform[1] = rotMat * worldTransform[1];
			worldTransform[2] = rotMat * worldTransform[2];
		}
	}
	//glm::mat4 oldTrans = worldTransform;
	//glm::mat4 trans;
	//glm::vec3 worldUp = glm::vec3(0, 1, 0);[]

	//// Right
	//glm::vec3 oldForward = glm::vec3(oldTrans[2].x, oldTrans[2].y, oldTrans[2].z);
	//trans[0] = glm::normalize(glm::vec4(glm::cross(worldUp, oldForward), 0));
	////Up
	//glm::vec3 newRight = glm::vec3(trans[0].x, trans[0].y, trans[0].z);
	//trans[1] = glm::normalize(glm::vec4(glm::cross(oldForward, newRight), 0));
	////Forward
	//trans[2] = glm::normalize(oldTrans[2]);

	////Position
	//trans[3] = oldTrans[3];

	//worldTransform = trans;
}
