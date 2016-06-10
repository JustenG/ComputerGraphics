#include "Components\RigidBody.h"
#include "Physics\PhysXManager.h"

RigidBody::RigidBody()
{
	m_physXManager = PhysXManager::GetInstance();
}

RigidBody::~RigidBody()
{
}

void RigidBody::Start()
{
	
}