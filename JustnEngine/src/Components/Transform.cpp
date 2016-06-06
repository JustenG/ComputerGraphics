#include "Components\Transform.h"
#include "Components\ComponentManager.h"
#include "all_includes.h"

Transform::Transform()
{
	m_pComponentManager = ComponentManager::GetInstance();
	m_pParent = nullptr;
	m_isDirty = true;

	m_globalTransformMatrix = glm::mat4(1);
	m_localTransformMatrix = glm::mat4(1);
	m_position = glm::vec3(0);
	m_rotation = glm::vec3(0);
	m_scale = glm::vec3(1);

	m_dataBinder = new TransformData(
		m_position,
		m_rotation,
		m_scale);

	vector<string> names;
	names.push_back("Position");
	names.push_back("Rotation");
	names.push_back("Scale");
	m_dataBinder->SetNames(names);

}
Transform::~Transform()
{
}

BaseData* Transform::ToData()
{
	return m_dataBinder->Get();
}
void Transform::FromData(BaseData* newData)
{
	if (Validate(newData))
	{
		m_dataBinder->Set(newData);

		m_isDirty = true;

	}
	else;
	//Data not valid
}
bool Transform::Validate(BaseData* newData)
{
	vector<BaseData*> children = newData->GetChildren();

	if (!DataConverter::DataEqualsPrimitive(m_position, children[0]) ||
		!DataConverter::DataEqualsPrimitive(m_rotation, children[1]) ||
		!DataConverter::DataEqualsPrimitive(m_scale, children[2])	 )
	{
		m_isDirty = true;
	}

	return m_isDirty;
}

void Transform::AddChild(Transform* newChild)
{
	newChild->m_pParent = this;
	m_pChildren.push_back(newChild);
}

void Transform::RemoveChild(int childsIndex)
{
	std::vector<Transform*> tempTransform;

	for (unsigned int i = childsIndex + 1; i < m_pChildren.size(); ++i)
	{
		tempTransform.push_back(m_pChildren[i]);
	}

	for (unsigned int i = 0; i < tempTransform.size(); ++i)
	{
		m_pChildren[i + childsIndex] = tempTransform[i];
	}

	m_pChildren.pop_back();
}

void Transform::SwapChild(int first, int second)
{
	Transform* tempTransform = m_pChildren[first];

	m_pChildren[first] = m_pChildren[second];

	m_pChildren[second] = tempTransform;
}

void Transform::MoveChild(int childIndex, int newIndex)
{
	if (childIndex == newIndex)
		return;

	int moveBy = newIndex - childIndex;

	if (moveBy < 0)
	{
		for (int i = 0; i > moveBy; --i)
		{
			SwapChild(childIndex - i, childIndex -1 - i);
		}
	}
	else
	{
		for (int i = 0; i < moveBy; ++i)
		{
			SwapChild(childIndex + i, childIndex + 1 + i);
		}
	}
}

void Transform::Update()
{
	if (!m_isDirty)
		return;

	glm::mat4 localTransform(1);

	localTransform *= glm::translate(localTransform, m_position);

	glm::mat4 rotationMatrix(1);
	rotationMatrix *= glm::axisAngleMatrix(glm::vec3(1, 0, 0), m_rotation.x);
	rotationMatrix *= glm::axisAngleMatrix(glm::vec3(0, 1, 0), m_rotation.y);
	rotationMatrix *= glm::axisAngleMatrix(glm::vec3(0, 0, 1), m_rotation.z);
	localTransform *= rotationMatrix;

	localTransform *= glm::scale(localTransform, m_scale);

	m_localTransformMatrix = localTransform;

	m_isDirty = false;
}

void Transform::UpdateWorldTransform()
{
	if(m_pParent != nullptr)
		m_globalTransformMatrix = m_pParent->GetMatrix() * m_localTransformMatrix;
	else
		m_globalTransformMatrix = m_localTransformMatrix;
}