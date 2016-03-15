#pragma once
#include "Application.h"
#include "Assets\Mesh.h"
#include "Assets\Shader.h"
#include "Cameras\Camera.h"

class Mesh;

class TestEngineApp : public Application
{
public:
	TestEngineApp();
	virtual ~TestEngineApp();

	void Update();
	void Draw();
	void Initialize();
	void Destroy();

private:

	Mesh* m_pModel;

};

