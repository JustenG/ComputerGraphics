#pragma once

#include "Camera.h"
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

class FlyCamera : public Camera
{
public:
	FlyCamera();
	virtual ~FlyCamera();

	//FlyCamera
	float speed;
	glm::vec3 up;
	virtual void Update(float deltaTime, GLFWwindow* window);
	void SetSpeed(float speed);

	void GetInput(float deltaTime, GLFWwindow* window);
	void MouseContol(float deltaTime, GLFWwindow* window);

private:

	int prevMouseX;
	int prevMouseY;


};

