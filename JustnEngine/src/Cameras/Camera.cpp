#include "Cameras\Camera.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

Camera::Camera()
{
	rotationMatrix = mat4(1);
	forward = mat4(1);
	forwardVec = vec3(1);
}


Camera::~Camera()
{
}

void Camera::Update(float deltaTime, GLFWwindow* window)
{

}



void Camera::SetPerspective(float fieldOfView, float aspectRatio, float _near, float _far)
{
	projectionTransform = glm::perspective(fieldOfView * glm::pi<float>() / 180.f, aspectRatio, _near, _far);
}

void Camera::SetLookAt(vec3 from, vec3 to, vec3 up)
{
	worldTransform = glm::inverse(glm::lookAt(from, to, up));
}

void Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * GetView();
}

vec3 Camera::GetPos()
{;
	return vec3(worldTransform[3][0], worldTransform[3][1], worldTransform[3][2]);
}

void Camera::MovePos(vec3 pos)
{
	worldTransform[3] = glm::vec4( vec3(worldTransform[3]) + pos, 1 );
}

mat4 Camera::GetView()
{
	return glm::inverse(worldTransform);
}
mat4 Camera::GetProjection()
{
	return projectionTransform;
}
mat4 Camera::GetProjectionView()
{
	return projectionViewTransform;
}
mat4 Camera::GetWorldTransform()
{
	return worldTransform;
}

