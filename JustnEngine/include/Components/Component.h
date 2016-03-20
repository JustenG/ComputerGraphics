#pragma once

class Component
{
public:
	Component();
	~Component();

	virtual void Update() = 0;

	void SetTransformIndex(int transformIndex);
	int GetTransformIndex();

private:

	int m_transformIndex;

};