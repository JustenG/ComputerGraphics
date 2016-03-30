#pragma once
#include "Application.h"

class MeshFile;
class GameObject;
class Camera;

class TestEngineApp : public Application
{
public:
	TestEngineApp() {};
	virtual ~TestEngineApp();

	void Initialise() override;
	void EarlyUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void Draw() override;
	void Destroy() override;

private:

	GameObject* m_entity;
	MeshFile* m_pModel;
	Camera* m_pFlyCam;

	glm::vec3 m_lightPos;

};

