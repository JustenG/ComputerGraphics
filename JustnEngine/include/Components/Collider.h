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

	void Update() override {};

	void Start();

private:

	PhysXManager* m_physXManager;
	physx::PxRigidActor* m_actor;

	void InitBox();
	void InitSphere();
	void InitCapsules();
	void InitPlane();

	void InitMeshConvex();
	void InitMeshConcave();
	void InitTerrain();


	bool m_isBox;
	bool m_isSphere;
	bool m_isCapsules;
	bool m_isPlane;

	bool m_isMeshConvex;
	bool m_isMeshConcave;
	bool m_isTerrain;


};