#include "Components\Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetMatrix()
{
	return m_transformMatrix;
}

glm::vec3 Transform::GetPosition()
{
	return m_position;
}


void Transform::Update()
{

}