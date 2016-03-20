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
	//m_pModel->Render();

	DrawGizmos();
}
