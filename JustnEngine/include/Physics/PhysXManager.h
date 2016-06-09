#pragma once

#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <pvd/PxVisualDebugger.h>
using namespace physx;

class PhysXManager
{
public:
	static PhysXManager* GetInstance();
	~PhysXManager();
	PhysXManager(PhysXManager const&) = delete;
	void operator=(PhysXManager const&) = delete;

	void AddActorToScene(PxActor* PhysXActor);
	PxHeightField* CreateHeightField(PxHeightFieldDesc hfDesc);


private:

	PhysXManager();
	static PhysXManager* m_instance;

	static PxDefaultErrorCallback m_DefaultErrorCallback;
	static PxDefaultAllocator m_DefaultAllocatorCallback;

	PxFoundation* m_PhysicsFoundation;
	PxPhysics* m_Physics;
	PxProfileZoneManager* m_ProfileZoneManager;
	PxScene* m_PhysicsScene;
	PxSimulationFilterShader m_DefaultFilterShader = PxDefaultSimulationFilterShader;
	PxCooking* m_Cooking;


};

