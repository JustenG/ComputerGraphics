#pragma once
#include <gl_core_4_4.h>
#include <glm/glm.hpp>

#include "global_includes.h"

#include "Components\Component.h"
#include "Rendering\FrameBuffer.h"

#include "Transform.h"
#include "Utilities\Data.h"

struct GLFWwindow;
//class Transform;

class Camera : public Component<Transform>
{
public:
	Camera();
	Camera(glm::ivec2 resolution);
	virtual ~Camera();

	void Update();
	void Update(Transform transform);

	void SetToMain();
	void SetToCamera();
	void SetToLight();

	FrameBuffer& GetFBO() { return m_FBO; };
	Shader* GetShader() { return m_FBO.GetShader(); };
	glm::ivec2 GetResolution();
	
	void SetShader(Shader* shader) { m_FBO.SetShaderProgram(shader); };	
	void SetResolution(glm::ivec2 resolution);

	void SetPerspective();
	void SetOrthograpghic();
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void UpdateProjectionViewTransform();
	glm::vec3 GetPosition();
	//void MovePos(glm::vec3 position);

	void Bind();
	void Unbind();

	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::mat4 GetProjectionView();
	glm::mat4 GetWorldTransform();

protected:

	FrameBuffer m_FBO;

	glm::mat4 worldTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

	bool m_isMainCamera;
	bool m_renderToTexture;

	bool m_orthographic;
	//Perspective
	float m_fieldOfView;
	float m_aspectRatio;
	//Orthographic
	float m_orthoSize;
	//Planes
	float m_nearPlane;
	float m_farPlane;

	glm::ivec2 m_resolution;

//-----------------------------------------
//-----------------------------------------

//Data of Class
//-----------------------------------------
//-----------------------------------------
public:
	//Data Type
	using CameraData = decltype(Make::CreateDataBinderType(
		m_isMainCamera,
		m_orthographic,
		m_fieldOfView,
		m_orthoSize,
		m_nearPlane,
		m_farPlane,
		m_resolution));

	BaseData* ToData() override;
	void FromData(BaseData* newData) override;
	bool Validate(BaseData* newData);
private:
	CameraData* m_dataBinder;
//-----------------------------------------
//-----------------------------------------
};


