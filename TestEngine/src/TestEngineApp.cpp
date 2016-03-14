#include "TestEngineApp.h"
#include "Assets\Mesh.h"


TestEngineApp::TestEngineApp()
{
	m_pModel = new Mesh();
<<<<<<< HEAD
	m_pModel->LoadFile("data/models/soulspear/soulspear.fbx");
	m_pModel->LoadShader("data/shaders/defultVertexShader.txt","data/shaders/defultFragmentShader.txt");
=======
	m_pModel->LoadFile("/data/models/soulspear/soulspear.fbx");
	//m_pModel->LoadShader("/data/shaders/defultVertexShader.txt","data/shaders/defultFragmentShader.txt");
>>>>>>> 7b5775473875dc19d44cc6928b9a85feb39b4c09
}

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Update()
{

}
void TestEngineApp::Draw()
{
<<<<<<< HEAD
	m_pModel->Render(GetCamera());
=======
	//m_pModel->Render(GetCamera());
>>>>>>> 7b5775473875dc19d44cc6928b9a85feb39b4c09
	DrawGizmos();
}
