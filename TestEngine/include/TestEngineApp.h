#pragma once
#include "Application.h"
#include "Assets\Mesh.h"
#include "Assets\Shader.h"
#include "Cameras\Camera.h"
#include "Cameras\FlyCamera.h"

class Mesh;

class TestEngineApp : public Application
{
public:
	TestEngineApp();
	virtual ~TestEngineApp();

	void Update();
	void Draw();
	void Initialise();
	void Destroy();

private:

	Mesh* m_pModel;

	FlyCamera* m_pFlyCam;

};

