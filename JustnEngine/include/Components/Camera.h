#pragma once

#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Components\Component.h"
#include "Rendering\FrameBuffer.h"

struct GLFWwindow;
class Transform;

class Camera : public Component
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
	glm::mat4 worldTransform;

	bool m_orthographic;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
	//Perspective
	float m_fieldOfView;
	float m_aspectRatio;
	//Orthographic
	float m_orthoSize;
	//Planes
	float m_nearPlane;
	float m_farPlane;

	glm::ivec2 m_resolution;

	bool m_isMainCamera;
	bool m_renderToTexture;

	FrameBuffer m_FBO;

};

