#pragma once
#include "Components\Component.h"
#include "Components\Collider.h"

class PhysXManager;

class RigidBody : public Component<Transform>
{
public:
	RigidBody();
	~RigidBody();

	void Update() override {};


	void Start();

private:

	PhysXManager* m_physXManager;

};