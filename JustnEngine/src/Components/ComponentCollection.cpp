#pragma once
class BaseComponent
{
public:
	BaseComponent() {};
	~BaseComponent() {};

	virtual void Update() = 0;
};

