#include "TestEngineApp.h"
#include "Assets\AssetLoader.h"


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
	AssetManager::GetInstance()->LoadShader("data/shaders/defultVertexShader.vert", "data/shaders/defultFragmentShader.frag", "DefultShader");
	m_pModel->SetShader(AssetManager::GetInstance()->GetAsset<Shader>("DefultShader"));
}

void TestEngineApp::Destroy()
{
	delete m_pModel;
}

void TestEngineApp::EarlyUpdate()
{

}

void TestEngineApp::Update()
{

}

void TestEngineApp::LateUpdate()
{


}
void TestEngineApp::Draw()
{
	//m_pModel->Render();

	DrawGizmos();
}
