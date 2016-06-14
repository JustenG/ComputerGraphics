#include "Components\Particles.h"
#include "Physics\PhysXManager.h"
#include "Physics\ParticleEmitter.h"
#include "Entitys\GameObject.h"
#include "Components\Transform.h"

Particles::Particles()
{
	m_physXManager = PhysXManager::GetInstance();
	m_isFluid = true;

	m_particleFluid = nullptr;
	m_particleSystem = nullptr;
	m_particleEmitter = nullptr;

	m_myTransform = nullptr;
	m_lifeTime = 20;
}

Particles::~Particles()
{
}

void Particles::Update(float deltaTime)
{
	if (m_particleEmitter)
	{
		if(!m_myTransform)	m_myTransform = GetGameObject()->GetComponent<Transform>();
		glm::vec3 pos = m_myTransform->GetPosition();

		m_particleEmitter->SetPosition(PxVec3(pos.x, pos.y, pos.z));
		m_particleEmitter->SetLifeTime(m_lifeTime);
		m_particleEmitter->Update(deltaTime);
	}
}

void Particles::Render()
{
	if(m_particleEmitter)
		m_particleEmitter->RenderParticles();
}

void Particles::Start()
{
	//create our particle system
	if (m_isFluid)
	{
		// create particle system in PhysX SDK
		// set immutable properties.
		m_maxParticles = 4000;
		bool perParticleRestOffset = false;

		if (m_particleFluid)
			m_particleFluid->release();
		m_particleFluid = m_physXManager->GetPhysics()->createParticleFluid(m_maxParticles, perParticleRestOffset);

		m_particleFluid->setRestParticleDistance(.3f);
		m_particleFluid->setDynamicFriction(0.1);
		m_particleFluid->setStaticFriction(0.1);

		m_particleFluid->setDamping(0.1);
		m_particleFluid->setParticleMass(.1);
		m_particleFluid->setRestitution(0);

		//pf->setParticleReadDataFlag(PxParticleReadDataFlag::eDENSITY_BUFFER, true);
		m_particleFluid->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY, true);
		m_particleFluid->setStiffness(100);

		if (m_particleFluid)
		{
			if (!m_myTransform)	m_myTransform = GetGameObject()->GetComponent<Transform>();
			glm::vec3 pos = m_myTransform->GetPosition();

			m_physXManager->AddActorToScene(m_particleFluid);
			m_particleEmitter = new ParticleEmitter(m_maxParticles, PxVec3(pos.x, pos.y, pos.z), m_particleFluid, .1);
			m_particleEmitter->SetStartVelocityRange(-0.001f, -250.0f, -0.001f, 0.001f, -250.0f, 0.001f);
		}
	}
	else
	{
		// create particle system in PhysX SDK
		// set immutable properties.
		m_maxParticles = 4000;
		bool perParticleRestOffset = false;

		if (m_particleSystem)
			m_particleSystem->release();
		m_particleSystem = m_physXManager->GetPhysics()->createParticleSystem(m_maxParticles, perParticleRestOffset);


		//m_particleSystem->setDynamicFriction(0.1);
		//m_particleSystem->setStaticFriction(0.1);
		m_particleSystem->setDamping(0.1);
		m_particleSystem->setParticleMass(.1);
		m_particleSystem->setRestitution(0);

		m_particleSystem->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY, true);

		if (m_particleSystem)
		{
			if (!m_myTransform)	m_myTransform = GetGameObject()->GetComponent<Transform>();
			glm::vec3 pos = m_myTransform->GetPosition();

			m_physXManager->AddActorToScene(m_particleSystem);
			m_particleEmitter = new ParticleEmitter(m_maxParticles, PxVec3(pos.x, pos.y, pos.z), m_particleSystem, .1);
			m_particleEmitter->SetStartVelocityRange(-0.001f, -250.0f, -0.001f, 0.001f, -250.0f, 0.001f);
		}
	}
}

void Particles::End()
{
	delete m_particleEmitter;
	m_particleEmitter = nullptr;
}