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

	void Update();

private:

	Transform* m_pParent;
	std::vector<Transform*> m_pChildren;

	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::quat m_scale;

};