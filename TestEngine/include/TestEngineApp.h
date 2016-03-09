#pragma once
#include "Application.h"

class Mesh;

class TestEngineApp : public Application
{
public:
	TestEngineApp();
	virtual ~TestEngineApp();

	void Update();
	void Draw();

private:

	Mesh* m_pModel;

};

