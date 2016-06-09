#include "Components\Collider.h"
#include "Components\Transform.h"
#include "Components\Terrain.h"
#include "Entitys\GameObject.h"
#include "Physics\PhysXManager.h"

Collider::Collider()
{
	m_physXManager = PhysXManager::GetInstance();
}

Collider::~Collider()
{
}

void Collider::Init()
{
	
}

void Collider::InitBox()
{

}
void Collider::InitSphere()
{

}
void Collider::InitCapsules()
{

}
void Collider::InitPlane()
{

}

void Collider::InitMeshConvex()
{

}
void Collider::InitMeshConcave()
{

}
void Collider::InitTerrain()
{
	Terrain* myTerrain = GetGameObject()->GetComponent<Terrain>();
	Transform* myTransform = GetGameObject()->GetComponent<Transform>();
	int size = myTerrain->GetSize();

	PxHeightFieldDesc hfDesc;
	hfDesc.format = PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns = size;
	hfDesc.nbRows = size;
	hfDesc.samples.data = myTerrain->GetHeightMap();
	hfDesc.samples.stride = sizeof(PxHeightFieldSample);
	hfDesc.thickness = -100.0f;

	PxHeightField* heightField = m_physXManager->CreateHeightField(hfDesc);
	
	PxHeightFieldGeometry hfGeom(heightField, PxMeshGeometryFlags(), myTransform->GetScale().y, myTransform->GetScale().x, myTransform->GetScale().z);
	PxTransform pose = PxTransform(PxVec3(0.0f, 0, 0.0f));
	PxShape* heightmap = _pXactor->createShape((PxHeightFieldGeometry)hfGeom, *g_PhysicsMaterial, pose);
}