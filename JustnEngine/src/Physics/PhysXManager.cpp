#include "Physics\PhysXManager.h"

PhysxManager * PhysxManager::GetInstance()
{
	if (!m_instance)
		m_instance = new PhysxManager();

	return m_instance;
};

PhysxManager::PhysxManager()
{
	m_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
	if (!m_PhysicsFoundation)
		printf("PxCreateFoundation failed!");

	bool recordMemoryAllocations = true;
	m_ProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(m_PhysicsFoundation);
	if (!m_ProfileZoneManager)
		printf("PxProfileZoneManager::createProfileZoneManager failed!");

	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_PhysicsFoundation, PxTolerancesScale(), recordMemoryAllocations, m_ProfileZoneManager);
	if (!m_Physics)
		printf("PxCreatePhysics failed!");

	m_Cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_PhysicsFoundation, PxTolerancesScale());
	if (!m_Cooking)
		printf("PxCreateCooking failed!");

	if (!PxInitExtensions(*m_Physics))
		printf("PxInitExtensions failed!");
	//create physics material g_PhysicsMaterial = g_Physics->createMaterial(0.5f, 0.5f,	.5f);
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.0f, 0);
	sceneDesc.filterShader = &physx::PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);

	m_PhysicsScene = m_Physics->createScene(sceneDesc);

}

PhysxManager::~PhysxManager()
{
}