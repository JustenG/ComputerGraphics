#pragma once
#include "Components\Transform.h"

#include <PxPhysicsAPI.h>
#include <PxScene.h>

class PhysXManager;
class ParticleEmitter;

class Particles : public Component<Transform>
{
public:
	Particles();
	~Particles();

	void Update() override {};
	void Update(float deltaTime);
	void Render();


	void Start();
	void End();

private:

	PhysXManager* m_physXManager;
	ParticleEmitter* m_particleEmitter;
	physx::PxParticleFluid*  m_particleFluid;
	physx::PxParticleSystem* m_particleSystem;
	physx::PxU32 m_maxParticles;
	bool m_isFluid;

	Transform* m_myTransform;
	float m_lifeTime;


};