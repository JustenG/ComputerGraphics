#include "TestEngineApp.h"
#include "Assets\Mesh.h"


TestEngineApp::TestEngineApp()
{
	m_pModel = new Mesh();
	m_pModel->LoadFile("data/models/soulspear/soulspear.fbx");
	m_pModel->LoadShader("data/shaders/defultVertexShader.txt","data/shaders/defultFragmentShader.txt");
}

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Update()
{

}
void TestEngineApp::Draw()
{
	m_pModel->Render(GetCamera());
	DrawGizmos();
}
