#pragma once
#include <PxPhysicsAPI.h>
#include <glm/ext.hpp>
using namespace physx;
using namespace std;

//simple struct for our particles

struct Particle
{
	bool active;
	float maxTime;
};


//simple class for particle emitter.  For a real system we would make this a base class and derive different emitters from it by making functions virtual and overloading them.
class ParticleEmitter
{
	
public:
	ParticleEmitter(int _maxParticles ,PxVec3 _position, PxParticleFluid*  _pf, float _releaseDelay);
	ParticleEmitter(int _maxParticles, PxVec3 _position, PxParticleSystem* _ps, float _releaseDelay);
	~ParticleEmitter();

	void SetStartVelocityRange(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
	void SetPosition(PxVec3 pos) { m_position = pos; };
	void SetLifeTime(float lifeTime) { m_particleMaxAge = lifeTime; };

	void Update(float delta);
	void ReleaseParticle(int);
	bool TooOld(int);
	void RenderParticles();

private:

	int GetNextFreeParticle();
	bool AddPhysXParticle(int particleIndex);

	bool				m_isFluid;

	PxParticleFluid*	m_pf;
	PxParticleSystem*	m_ps;
	int					m_rows;
	int					m_cols;
	int					m_depth;


	Particle*			m_activeParticles;
	int					m_maxParticles;
	float				m_releaseDelay;
	int					m_numberActiveParticles;

	float				m_time;
	float				m_respawnTime;
	float				m_particleMaxAge;

	PxVec3				m_position;
	PxVec3				m_minVelocity;
	PxVec3				m_maxVelocity;
};