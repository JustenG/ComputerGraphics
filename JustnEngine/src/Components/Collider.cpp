#include "Components\Collider.h"
#include "Components\Transform.h"
#include "Components\Terrain.h"
#include "Components\RigidBody.h"
#include "Components\PlayerController.h"
#include "Entitys\GameObject.h"
#include "Physics\PhysXManager.h"

#include "all_includes.h"

#include <algorithm> 

Collider::Collider()
{
	m_physXManager = PhysXManager::GetInstance();
	m_physics = m_physXManager->GetPhysics();
	m_cooking = m_physXManager->GetCooking();
	m_physXMaterial = m_physics->createMaterial(0.5f, 0.5f, 0.5f);

	m_xScale = 1;
	m_yScale = 1;
	m_zScale = 1;

	m_actor = nullptr;
	m_shape = nullptr;

	m_isBox = true;
	m_isSphere = false;
	m_isCapsules = false;
	m_isPlane = false;

	m_isMeshConvex = false;
	m_isMeshConcave = false;
	m_isTerrain = false;

	m_shapeIndex = 0;

	m_dataBinder = new ColliderDataBinder(
		m_isBox,
		m_isSphere,
		m_isCapsules,
		m_isPlane,
		m_isMeshConvex,
		m_isMeshConcave,
		m_isTerrain);

	vector<string> names;
	names.push_back("Box");
	names.push_back("Sphere");
	names.push_back("Capsules");
	names.push_back("Plane");
	names.push_back("Convex Mesh");
	names.push_back("Concave Mesh");
	names.push_back("Terrain");
	m_dataBinder->SetNames(names);


}
BaseData* Collider::ToData()
{
	return m_dataBinder->Get();
}
void Collider::FromData(BaseData* newData)
{
	if (Validate(newData))
	{
		m_dataBinder->Set(newData);
	}
	else;
	//Data not valid
}
bool Collider::Validate(BaseData* newData)
{
	vector<BaseData*> children = newData->GetChildren();
	bool isDirty = false;
	int newIndex = -1;

	if (!DataConverter::DataEqualsPrimitive(m_isBox, children[0]))
	{
		newIndex = 0;
		isDirty = true;
	}
	if(!DataConverter::DataEqualsPrimitive(m_isSphere, children[1]))
	{
		newIndex = 1;
		isDirty = true;
	}
	if (!DataConverter::DataEqualsPrimitive(m_isCapsules, children[2]))
	{
		newIndex = 2;
		isDirty = true;
	}
	if (!DataConverter::DataEqualsPrimitive(m_isPlane, children[3]))
	{
		newIndex = 3;
		isDirty = true;
	}
	if (!DataConverter::DataEqualsPrimitive(m_isMeshConvex, children[4]))
	{
		newIndex = 4;
		isDirty = true;
	}
	if (!DataConverter::DataEqualsPrimitive(m_isMeshConcave, children[5]))
	{
		newIndex = 5;
		isDirty = true;
	}
	if(!DataConverter::DataEqualsPrimitive(m_isTerrain, children[6]))
	{
		newIndex = 6;
		isDirty = true;
	}

	if (isDirty)
	{
		DataConverter::SetPrimitive(children[m_shapeIndex], false);
		m_shapeIndex = newIndex;
	}


	return isDirty;
}

Collider::~Collider()
{

}

void Collider::Update()
{
	if (m_actor == nullptr)
		return;
	m_myTransform = GetGameObject()->GetComponent<Transform>();
	PxVec3 pos = m_actor->getGlobalPose().p;
	PxQuat rot = m_actor->getGlobalPose().q;
	m_myTransform->SetPosition(pos.x, pos.y, pos.z);
	m_myTransform->SetRotation(rot.x, rot.y, rot.z, rot.w);
}

void Collider::Start()
{
	if (m_shape != nullptr)
		m_shape->release();

	m_myTransform = GetGameObject()->GetComponent<Transform>();

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
	m_shape = m_physics->createShape(PxBoxGeometry(m_myTransform->GetScale().x * m_xScale, m_myTransform->GetScale().y * m_yScale, m_myTransform->GetScale().z * m_zScale), *m_physXMaterial);
	SetActor();
}
void Collider::InitSphere()
{
	float position[] = { m_myTransform->GetScale().x * m_xScale, m_myTransform->GetScale().y * m_yScale, m_myTransform->GetScale().z * m_zScale };
	float radius = *std::max_element(position, position + 3);

	m_shape = m_physics->createShape(PxSphereGeometry(radius), *m_physXMaterial);
	SetActor();
}
void Collider::InitCapsules()
{
	float position[] = { m_myTransform->GetScale().x * m_xScale, m_myTransform->GetScale().z * m_zScale };
	float radius = *std::max_element(position, position + 2);

	m_shape = m_physics->createShape(PxCapsuleGeometry(radius, m_myTransform->GetScale().y/2 * m_yScale), *m_physXMaterial);
	SetActor();
}
void Collider::InitPlane()
{
	m_shape = m_physics->createShape(PxPlaneGeometry(), *m_physXMaterial);
	SetActor();
}

void Collider::InitMeshConvex()
{

}
void Collider::InitMeshConcave()
{

}
void Collider::InitTerrain()
{
	m_myTransform = GetGameObject()->GetComponent<Transform>();
	Terrain* myTerrain = GetGameObject()->GetComponent<Terrain>();
	if (myTerrain == nullptr)
	{
		printf("Error: GameObject has not Terrain");
		return;
	}

	int size = myTerrain->GetSize();

	PxHeightFieldDesc hfDesc;
	hfDesc.format = PxHeightFieldFormat::eS16_TM;
	hfDesc.nbColumns = size;
	hfDesc.nbRows = size;
	hfDesc.samples.data = myTerrain->GetHeightMap();
	hfDesc.samples.stride = sizeof(PxHeightFieldSample);
	hfDesc.thickness = -100.0f;

	PxHeightField* heightField = m_cooking->createHeightField(hfDesc, m_physics->getPhysicsInsertionCallback());
	PxHeightFieldGeometry hfGeom(heightField, PxMeshGeometryFlags(), m_myTransform->GetScale().y, m_myTransform->GetScale().z, m_myTransform->GetScale().x);

	m_shape = m_physics->createShape((PxHeightFieldGeometry)hfGeom, *m_physXMaterial);

	SetActor();
}

void Collider::SetActor()
{
	if (GetGameObject()->GetComponent<PlayerController>() != nullptr)
	{
		return;
	}

	PxTransform pose = PxTransform(PxVec3(m_myTransform->GetPosition().x, m_myTransform->GetPosition().y, m_myTransform->GetPosition().z));

	if (m_actor != nullptr)
	{
		m_physXManager->RemoveActorFromScene(m_actor);
		m_actor->release();
	}

	if (GetGameObject()->GetComponent<RigidBody>() != nullptr)
	{
		if (GetGameObject()->GetStaticTag() == true)
			m_actor = PxCreateStatic(*m_physics, pose, *m_shape);
		else
			m_actor = PxCreateDynamic(*m_physics, pose, *m_shape, 1);
	}
	else
	{
		m_actor = PxCreateStatic(*m_physics, pose, *m_shape);
	}
	m_physXManager->AddActorToScene(m_actor);
}