#include "Physics\PhysXManager.h"

PhysXManager* PhysXManager::m_instance = nullptr;

PhysXManager * PhysXManager::GetInstance()
{
	if (!m_instance)
		m_instance = new PhysXManager();

	return m_instance;
};

PhysXManager::PhysXManager()
{
	m_PhysicsFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, m_DefaultAllocatorCallback, m_DefaultErrorCallback);
	if (!m_PhysicsFoundation)
		printf("PxCreateFoundation failed!");

	bool recordMemoryAllocations = true;

	m_ProfileVisualDebugger = PxCreatePvd(*m_PhysicsFoundation);
	PxPvdTransport* transport = PxDefaultPvdFileTransportCreate(NULL);
	m_ProfileVisualDebugger->connect(*transport, PxPvdInstrumentationFlag::eALL);

	if (!m_ProfileVisualDebugger)
		printf("PxCreatePvd failed!");

	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_PhysicsFoundation, PxTolerancesScale(), recordMemoryAllocations, m_ProfileVisualDebugger);
	if (!m_Physics)
		printf("PxCreatePhysics failed!");

	m_Cooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_PhysicsFoundation, PxTolerancesScale());
	if (!m_Cooking)
		printf("PxCreateCooking failed!");

	if (!PxInitExtensions(*m_Physics, m_ProfileVisualDebugger))
		printf("PxInitExtensions failed!");

	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.0f, 0);
	sceneDesc.filterShader = &physx::PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);

	m_PhysicsScene = m_Physics->createScene(sceneDesc);
	m_ControllerManager = PxCreateControllerManager(*m_PhysicsScene);

	//VISUAL DEBUGGER
	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------
	// setup connection parameters
	const char* pvd_host_ip = "127.0.0.1";
	// IP of the PC which is running PVD
	int port = 5425;
	// TCP port to connect to, where PVD is listening
	unsigned int timeout = 100;
	// timeout in milliseconds to wait for PVD to respond,
	//consoles and remote PCs need a higher timeout.

	m_PvdTransport = PxDefaultPvdSocketTransportCreate(pvd_host_ip, port, timeout);
	m_ProfileVisualDebugger->connect(*m_PvdTransport, PxPvdInstrumentationFlag::eALL);
	//---------------------------------------------------------------------------
	//---------------------------------------------------------------------------
}

PhysXManager::~PhysXManager()
{
	PxCloseExtensions();
	m_Cooking->release();
	m_Physics->release();
	m_ProfileVisualDebugger->release();
	m_PvdTransport->release();
	m_PhysicsFoundation->release();
}

void PhysXManager::Update(float deltaTime)
{
	m_PhysicsScene->simulate(deltaTime > 0.033f ? 0.033f : deltaTime);
	while (m_PhysicsScene->fetchResults() == false);
}

void PhysXManager::AddActorToScene(PxActor* PhysXActor)
{
	m_PhysicsScene->addActor(*PhysXActor);
}

void PhysXManager::RemoveActorFromScene(PxActor * PhysXActor)
{
	m_PhysicsScene->removeActor(*PhysXActor);
}