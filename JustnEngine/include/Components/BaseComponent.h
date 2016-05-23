#pragma once
#include "global_includes.h"
#include "Utilities\Data.h"
class GameObject;

class BaseComponent
{
public:
	BaseComponent() {};
	~BaseComponent() {};

	virtual void Update() = 0;

	void Init(GameObject* gameObject) 
	{
		m_gameObject = gameObject; 
	};
	void SetTransformIndex(int transformIndex) { m_transformIndex = transformIndex; };
	int GetTransformIndex() { return m_transformIndex; };

	GameObject* GetGameObject() { return m_gameObject; };

private:

	GameObject* m_gameObject;
	int m_transformIndex;

};

