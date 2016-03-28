#pragma once
#include "Components\Component.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

class ComponentManager;

class Transform : public Component
{
public:
	Transform();
	~Transform();

	glm::mat4 GetMatrix() { return m_globalTransformMatrix; };
	glm::vec3 GetPosition() { return m_position; };
	glm::vec3 GetRotation() { return m_rotation; };
	glm::vec3 GetScale() { return m_scale; };

	void SetPosition(glm::vec3 position) { m_position = position; };
	void SetRotation(glm::vec3 rotation) { m_rotation = rotation; };
	void SetScale	(glm::vec3 scale)	 { m_scale = scale; };
	void SetPosition(float x, float y, float z) { m_position = glm::vec3(x,y,z); };
	void SetRotation(float x, float y, float z) { m_rotation = glm::vec3(x, y, z); };
	void SetScale	(float x, float y, float z) { m_scale = glm::vec3(x, y, z); };

	Transform* GetParent() { return m_pParent; };
	std::vector<Transform*> GetChildren() { return m_pChildren; };

	void AddChild(Transform* transform);
	void RemoveChild(int index);
	void SwapChild(int first, int second);
	void MoveChild(int childIndex, int newIndex);

	void Update();
	void UpdateWorldTransform();
	void UpdateWorldTransform(glm::mat4 parentsTransform);

private:

	glm::mat4 m_localTransformMatrix;
	glm::mat4 m_globalTransformMatrix;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	ComponentManager* m_pComponentManager;

	Transform* m_pParent;
	std::vector<Transform*> m_pChildren;


};