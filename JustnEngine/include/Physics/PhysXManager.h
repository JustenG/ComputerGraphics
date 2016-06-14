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

	void Update(float deltaTime);
	void Init();
	void Shutdown();

	void AddActorToScene(PxActor* PhysXActor);
	void RemoveActorFromScene(PxActor* PhysXActor);
	PxPhysics* GetPhysics() { return m_Physics;	};
	PxControllerManager* GetControllerManager() { return m_ControllerManager; };


private:

	PhysXManager();
	static PhysXManager* m_instance;

	PxDefaultErrorCallback m_DefaultErrorCallback;
	PxDefaultAllocator m_DefaultAllocatorCallback;

	PxFoundation* m_PhysicsFoundation;
	PxPhysics* m_Physics;
	PxProfileZoneManager* m_ProfileZoneManager;
	PxScene* m_PhysicsScene;
	PxSimulationFilterShader m_DefaultFilterShader = PxDefaultSimulationFilterShader;
	PxCooking* m_Cooking;
	PxControllerManager* m_ControllerManager;


};

