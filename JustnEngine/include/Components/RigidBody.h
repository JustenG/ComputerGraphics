#pragma once
#include "Components\Component.h"
#include "Components\Collider.h"

class PhysXManager;

class RigidBody : public Component<Collider>
{
public:
	RigidBody();
	~RigidBody();

	void Init();

private:

	PhysXManager* m_physXManager;

};