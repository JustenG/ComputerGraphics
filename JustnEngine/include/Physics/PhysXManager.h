#pragma once

#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <pvd/PxVisualDebugger.h>

class PhysxManager
{
public:
	static PhysxManager* GetInstance();
	~PhysxManager();
	PhysxManager(PhysxManager const&) = delete;
	void operator=(PhysxManager const&) = delete;


private:

	PhysxManager();
	static PhysxManager* m_instance;

	PxDefaultErrorCallback m_DefaultErrorCallback;
	PxDefaultAllocator m_DefaultAllocatorCallback;

	PxFoundation* m_PhysicsFoundation;
	PxPhysics* m_Physics;
	PxProfileZoneManager* m_ProfileZoneManager;
	PxScene* m_PhysicsScene;
	PxSimulationFilterShader m_DefaultFilterShader = PxDefaultSimulationFilterShader;
	PxCooking* m_Cooking;


};

