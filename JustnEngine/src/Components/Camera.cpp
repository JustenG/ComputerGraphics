#include "Components\Camera.h"

#include <GLFW\glfw3.h>
#include "Components\Transform.h"
#include "all_includes.h"

Camera::Camera()
{
	m_fieldOfView	= 45;
	m_aspectRatio	= 16/9.0f;
	m_nearPlane		= 1;
	m_farPlane		= 1000;
	m_orthoSize		= 128;

	SetPerspective();
	SetLookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));

	m_dataBinder = new CameraData(
		m_isMainCamera,
		m_renderToTexture,
		m_orthographic,
		m_fieldOfView,
		m_aspectRatio,
		m_orthoSize,
		m_nearPlane,
		m_farPlane,
		m_resolution);
}
Camera::Camera(ivec2 resolution) : Camera()
{
	SetResolution(resolution);
}
BaseData* Camera::ToData()
{
	return m_dataBinder->Get();
}
void Camera::FromData(BaseData* newData)
{
	if(Validate(newData))
		m_dataBinder->Set(newData);
	else;
		//Data not valid
}
bool Camera::Validate(BaseData* newData)
{
	return true;
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

	SetPerspective();
}

void Camera::SetToCamera()
{
	m_isMainCamera = false;
	m_renderToTexture = true;
	SetResolution(glm::ivec2(1024));
	m_FBO.Reset(GetResolution());
	m_FBO.CreateBuffer(true, true);

	SetPerspective();
}

void Camera::SetToLight()
{
	m_isMainCamera = false;
	m_renderToTexture = true;
	SetResolution(glm::ivec2((int)m_orthoSize * 64));
	m_FBO.Reset(GetResolution());
	m_FBO.CreateBuffer(false, true);
	 
	SetOrthograpghic();
}

void Camera::SetResolution(glm::ivec2 resolution)
{
	m_resolution = resolution;
}
glm::ivec2 Camera::GetResolution()
{
	return m_resolution;
}

void Camera::SetPerspective()
{
	m_orthographic = false;
	projectionTransform = glm::perspective(m_fieldOfView, m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::SetOrthograpghic()
{
	m_orthographic = true;
	projectionTransform = glm::ortho<float>(-m_orthoSize, m_orthoSize, -m_orthoSize, m_orthoSize, -m_orthoSize, m_orthoSize);
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
	return vec3(worldTransform[3]);
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

