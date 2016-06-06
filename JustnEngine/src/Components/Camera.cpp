#include "Components\Camera.h"

#include <GLFW\glfw3.h>
#include "Components\Transform.h"
#include "all_includes.h"

#include "Entitys\GameObject.h"

Camera::Camera()
{
	m_isMainCamera	= false;
	m_orthographic	= false;
	m_fieldOfView	= 45;
	m_aspectRatio	= 16/9.0f;
	m_nearPlane		= 1;
	m_farPlane		= 1000;
	m_orthoSize		= 128;

	SetPerspective();
	SetLookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));

	m_dataBinder = new CameraData(
		m_isMainCamera,
		m_orthographic,
		m_fieldOfView,
		m_orthoSize,
		m_nearPlane,
		m_farPlane,
		m_resolution); 

	vector<string> names;
	names.push_back("Is Main Camera");
	names.push_back("Orthographic");
	names.push_back("Field Of View");
	names.push_back("Orthographic Size");
	names.push_back("Near Plane");
	names.push_back("Far Plane");
	names.push_back("Resolution");
	m_dataBinder->SetNames(names);

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
	if (Validate(newData))
	{
		m_dataBinder->Set(newData);

		if (m_isMainCamera)
			SetToMain();
		else
			SetToCamera();

		if (m_orthographic)
			SetOrthograpghic();
		else
			SetPerspective();
	}
	else;
		//Data not valid
}
bool Camera::Validate(BaseData* newData)
{
	vector<BaseData*> children = newData->GetChildren();
	bool isDirty = false;

	if (!DataConverter::DataEqualsPrimitive(m_isMainCamera, children[0]) ||
		!DataConverter::DataEqualsPrimitive(m_orthographic, children[1]) ||
		!DataConverter::DataEqualsPrimitive(m_fieldOfView,	children[2]) ||
		!DataConverter::DataEqualsPrimitive(m_orthoSize,	children[3]) ||
		!DataConverter::DataEqualsPrimitive(m_nearPlane,	children[4]) ||
		!DataConverter::DataEqualsPrimitive(m_farPlane,		children[5]) ||
		!DataConverter::DataEqualsPrimitive(m_resolution,	children[6]) )
	{
		isDirty = true;
	}

	return isDirty;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	worldTransform = GetGameObject()->GetComponent<Transform>()->GetMatrix();
	UpdateProjectionViewTransform();
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
	projectionTransform = glm::perspective(glm::radians(m_fieldOfView), m_aspectRatio, m_nearPlane, m_farPlane);
}

void Camera::SetOrthograpghic()
{
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

