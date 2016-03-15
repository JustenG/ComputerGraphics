#include "TestEngineApp.h"



TestEngineApp::TestEngineApp()
{
<<<<<<< HEAD
	m_pModel = new Mesh();
	m_pModel->LoadFile("/data/models/soulspear/soulspear.fbx");
	m_pModel->LoadShader("/data/shaders/defultVertexShader.txt","data/shaders/defultFragmentShader.txt");
=======
>>>>>>> b7907e781c7a70ceb5492f555ef3592566517786
}

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Initialize()
{
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
	m_pModel->GetShader()->SetModelUniform(glm::mat4(1));

	m_pModel->GetShader()->SetUniform("lightDir", glm::vec3(1, 0, 1));
	m_pModel->GetShader()->SetUniform("lightColour", glm::vec3( 1, 1, 1));
	m_pModel->GetShader()->SetUniform("cameraPos", GetCamera()->GetPos());

	int spec = 8;
	m_pModel->GetShader()->SetUniform("specPow", spec);

	m_pModel->Render(GetCamera());

	DrawGizmos();
}
