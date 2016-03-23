#include "TestEngineApp.h"

#include "Assets\AssetManager.h"
#include "Assets\Shader.h"
#include "Assets\Mesh.h"

#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Components\Camera.h"

#include "Entitys\EntityManager.h"
#include "Entitys\GameObject.h"

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Initialise()
{
	GetAssetManager()->LoadMesh("data/models/soulspear/soulspear.fbx", "spear");
	m_pModel = GetAssetManager()->GetAsset<Mesh>("spear");
	GetAssetManager()->LoadShader("data/shaders/defultVertexShader.vert", "data/shaders/defultFragmentShader.frag", "DefultShader");
	m_pModel->SetShader(GetAssetManager()->GetAsset<Shader>("DefultShader"));

	m_entity = GetEntityManager()->CreateEntity();
	
	m_entity->AddComponent<Transform>();
	m_entity->AddComponent<Camera>();
	m_entity->AddComponent<Mesh>();

	m_entity->GetComponent<Mesh>() = m_pModel;


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

}
