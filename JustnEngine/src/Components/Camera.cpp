#include "Components\Camera.h"

#include <GLFW\glfw3.h>
#include "Components\Transform.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

Camera::Camera()
{
	SetPerspective(45, 16 / 9.0f, 1, 1000);
	SetLookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));
}
Camera::Camera(glm::ivec2 resolution)
{
	SetPerspective(45, 16 / 9.0f, 1, 1000);
	SetLookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));
	SetResolution(resolution);
}

Camera::~Camera()
{

}

void Camera::Update()
{

}

void Camera::Update(Transform transform)
{
	worldTransform = transform.GetMatrix();
	UpdateProjectionViewTransform();
}

void Camera::Bind()
{
	m_FBO.Bind();
}

void Camera::Unbind()
{
	m_FBO.Unbind();
}

void Camera::SetToMain()
{
	m_isMainCamera = true;
	m_renderToTexture = false;
	m_FBO.Reset(GetResolution());
}

void Camera::SetToCamera()
{
	m_isMainCamera = false;
	m_renderToTexture = true;
	SetResolution(glm::ivec2(1024));
	m_FBO.Reset(GetResolution());
	m_FBO.CreateBuffer(true, true);
}

void Camera::SetToLight()
{
	m_isMainCamera = false;
	m_renderToTexture = true;
	SetResolution(glm::ivec2(1024));
	m_FBO.Reset(GetResolution());
	m_FBO.CreateBuffer(false, true);
}

void Camera::SetResolution(glm::ivec2 resolution)
{
	m_resolution = resolution;
}
glm::ivec2 Camera::GetResolution()
{
	return m_resolution;
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
	projectionViewTransform = GetProjection() * GetView();
}

vec3 Camera::GetPosition()
{
	return vec3(worldTransform[3][0], worldTransform[3][1], worldTransform[3][2]);
}

//void Camera::MovePos(vec3 pos)
//{
//	worldTransform[3] = glm::vec4( vec3(worldTransform[3]) + pos, 1 );
//}

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

