#include "TestEngineApp.h"



TestEngineApp::TestEngineApp()
{
}

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Initialise()
{
	m_pFlyCam = new FlyCamera();
	SetCamera(m_pFlyCam);
	SetGizmos(true);

	m_pModel = new Mesh();

	m_pModel->LoadFile("data/models/soulspear/soulspear.fbx");
	m_pModel->LoadShader("data/shaders/defultVertexShader.vert", "data/shaders/defultFragmentShader.frag");

	//m_pModel->UsingCameraUnifrom("CameraPos")
}

void TestEngineApp::Destroy()
{
	delete m_pModel;
}

void TestEngineApp::Update()
{

}
void TestEngineApp::Draw()
{
	//m_pModel->GetShader()->SetModelUniform(glm::mat4(1));

	//m_pModel->GetShader()->SetUniform("lightDir", glm::vec3(1, 0, 1));
	//m_pModel->GetShader()->SetUniform("lightColour", glm::vec3( 1, 1, 1));

	//int spec = 8;
	//m_pModel->GetShader()->SetUniform("specPow", spec);

	//m_pModel->Render();

	DrawGizmos();
}
