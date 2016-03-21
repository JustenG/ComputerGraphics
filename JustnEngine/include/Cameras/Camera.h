#pragma once

#define GLM_SWIZZLE 
#include <gl_core_4_4.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Components\Component.h"
#include "Rendering\FrameBuffer.h"

class GLFWwindow;
class Transform;

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	void Update();
	void Update(Transform transform);

	void SetPerspective(float fieldOfView, float aspectRatio, float _near, float _far);
	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void UpdateProjectionViewTransform();
	glm::vec3 GetPosition();
	//void MovePos(glm::vec3 position);

	void SetActive();

	glm::mat4 GetView();
	glm::mat4 GetProjection();
	glm::mat4 GetProjectionView();
	glm::mat4 GetWorldTransform();

protected:
	glm::mat4 worldTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;

	FrameBuffer m_pFBO;

};

