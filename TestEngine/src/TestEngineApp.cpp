#include "TestEngineApp.h"

#include "Assets\AssetManager.h"
#include "Assets\Shader.h"
#include "Assets\MeshFile.h"
#include "Assets\Material.h"

#include "Components\ComponentManager.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
#include "Components\Terrain.h"
#include "Components\Light.h"

#include "Entitys\EntityManager.h"
#include "Entitys\GameObject.h"

TestEngineApp::~TestEngineApp()
{
}

void TestEngineApp::Initialise()
{
	Transform* entityTransform;

	////Model
	//GetAssetManager()->LoadMeshFile("data/models/soulspear/soulspear.fbx", "spear");
	//m_pModel = GetAssetManager()->GetAsset<MeshFile>("spear");
	//GetAssetManager()->LoadShader("data/shaders/defultVertexShader.vert", "data/shaders/defultFragmentShader.frag", "DefultShader");
	//m_pModel->SetShader(GetAssetManager()->GetAsset<Shader>("DefultShader"));
	//m_pModel->CreateEntitys();

	////Terrain
	//m_entity = GetEntityManager()->CreateEntity();
	//m_entity->AddComponent<Transform>();
	//m_entity->AddComponent<Terrain>();
	//Terrain* entityTerrain = m_entity->GetComponent<Terrain>();
	//GetAssetManager()->LoadShader("data/shaders/terrain.vert", "data/shaders/terrain.frag", "terrainShader");
	//entityTerrain->SetShader(GetAssetManager()->GetAsset<Shader>("terrainShader"));
	//GetAssetManager()->CreateMaterial("terrainMaterial");
	//entityTerrain->SetMaterial(GetAssetManager()->GetAsset<Material>("terrainMaterial"));
	//entityTerrain->GenerateGrid(64,64);
	//entityTransform = m_entity->GetComponent<Transform>();
	//entityTransform->SetPosition(-16,-10,-16); 

	//Camera
	m_entity = GetEntityManager()->CreateEntity();
	m_entity->AddComponent<Transform>();
	//m_entity->AddComponent<Camera>(); 
	entityTransform = m_entity->GetComponent<Transform>(); 
	entityTransform->SetPosition(0, 2, 10);

	////Light 
	//m_entity = GetEntityManager()->CreateEntity();
	//m_entity->AddComponent<Transform>();
	//m_entity->AddComponent<Light>();
	//entityTransform = m_entity->GetComponent<Transform>();
	//entityTransform->SetPosition(5, 10, -5);
	//entityTransform->SetRotation(0, 0, 0);

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
	m_lightPos = glm::vec3(sin(glfwGetTime()), 1, -cos(glfwGetTime())) * 10;
	m_entity->GetComponent<Transform>()->SetPosition(m_lightPos);
}

void TestEngineApp::LateUpdate()
{


}
void TestEngineApp::Draw()
{

}
