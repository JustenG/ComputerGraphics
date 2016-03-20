#pragma once
#include "Components\Component.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class Transform : public Component
{
public:
	Transform();
	~Transform();

	glm::mat4 GetMatrix();
	glm::vec3 GetPosition();
	void Update();

private:

	Transform* m_pParent;
	std::vector<Transform*> m_pChildren;

	glm::mat4 m_transformMatrix;
	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::quat m_scale;

};