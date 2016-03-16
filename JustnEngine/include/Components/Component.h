#pragma once

class Component
{
public:
	Component();
	~Component();

	virtual void Update() = 0;

private:

};