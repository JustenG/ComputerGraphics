#pragma once
#include "Components\Collider.h"

class PhysXManager;

class RigidBody : public Component<Collider>
{
public:
	RigidBody();
	~RigidBody();

	void Update() override {};


	void Start();

private:

	PhysXManager* m_physXManager;

};