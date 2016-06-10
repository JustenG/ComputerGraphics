#include "Components\Collider.h"
#include "Components\Transform.h"
#include "Components\Terrain.h"
#include "Entitys\GameObject.h"
#include "Physics\PhysXManager.h"

Collider::Collider()
{
	m_physXManager = PhysXManager::GetInstance();

	m_actor = nullptr;

	m_isBox				= false;
	m_isSphere			= false;
	m_isCapsules		= false;	
	m_isPlane			= false;

	m_isMeshConvex		= false;
	m_isMeshConcave		= false;
	m_isTerrain			= false;
}

Collider::~Collider()
{

}

void Collider::Start()
{
	if (m_isBox)			InitBox();
	if (m_isSphere)			InitSphere();
	if (m_isCapsules)		InitCapsules();
	if (m_isPlane)			InitPlane();

	if (m_isMeshConvex)		InitMeshConvex();
	if (m_isMeshConcave)	InitMeshConcave();
	if (m_isTerrain)		InitTerrain();
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

	PxPhysics* physics = m_physXManager->GetPhysics();

	PxHeightField* heightField = physics->createHeightField(hfDesc);
	
	PxHeightFieldGeometry hfGeom(heightField, PxMeshGeometryFlags(), myTransform->GetScale().y, myTransform->GetScale().x, myTransform->GetScale().z);;
	PxMaterial* physXMaterial = physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxShape* m_shape = physics->createShape((PxHeightFieldGeometry)hfGeom, *physXMaterial);

	PxTransform pose = PxTransform(PxVec3(myTransform->GetPosition().x, myTransform->GetPosition().y, myTransform->GetPosition().z));

	if (m_actor != nullptr)
	{
		m_physXManager->RemoveActorFromScene(m_actor);
	}
	m_actor = PxCreateStatic(*physics, pose, *m_shape);
	m_physXManager->AddActorToScene(m_actor);
}