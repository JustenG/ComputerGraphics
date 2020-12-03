#pragma once
#include "Components\Component.h"
#include "Components\Transform.h"

#include <PxPhysicsAPI.h>
#include <PxScene.h>

class PhysXManager;

class Collider : public Component<Transform>
{
public:
	Collider();
	~Collider();

	void Update() override;

	void Start();

private:

	void SetActor();

	Transform* m_myTransform;

	PhysXManager* m_physXManager;
	physx::PxPhysics* m_physics;
	physx::PxCooking* m_cooking;
	physx::PxRigidActor* m_actor;
	physx::PxShape* m_shape;
	physx::PxMaterial* m_physXMaterial;

	float m_xScale;
	float m_yScale;
	float m_zScale;

	//Inits
	//----------------------
	//----------------------
	void InitBox();
	void InitSphere();
	void InitCapsules();
	void InitPlane();

	void InitMeshConvex();
	void InitMeshConcave();
	void InitTerrain();

	int m_shapeIndex;
	bool m_isBox;
	bool m_isSphere;
	bool m_isCapsules;
	bool m_isPlane;

	bool m_isMeshConvex;
	bool m_isMeshConcave;
	bool m_isTerrain;
	//----------------------
	//----------------------
	
//Data of Class
//-----------------------------------------
//-----------------------------------------
public:
	//Data Type
	using ColliderDataBinder = decltype(Make::CreateDataBinderType(
		m_isBox,
		m_isSphere,
		m_isCapsules,
		m_isPlane,
		m_isMeshConvex,
		m_isMeshConcave,
		m_isTerrain));

	BaseData* ToData() override;
	void FromData(BaseData* newData) override;
	bool Validate(BaseData* newData);
private:
	ColliderDataBinder* m_dataBinder;
	//-----------------------------------------
	//-----------------------------------------

};