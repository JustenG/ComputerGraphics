#include "Physics\ParticleEmitter.h"
#include <iostream>
#include<vector>
#include "Gizmos.h"


//constructor
ParticleEmitter::ParticleEmitter(int _maxParticles, PxVec3 _position,PxParticleFluid* _pf,float _releaseDelay)
{
	m_isFluid = true;

	m_releaseDelay			= _releaseDelay;
	m_maxParticles			= _maxParticles;				//maximum number of particles our emitter can handle

	//allocate an array
	m_activeParticles		= new Particle[m_maxParticles]; //array of particle structs
	m_time					= 0;							//time system has been running
	m_respawnTime			= 0;							//time for next respawn
	m_position				= _position;
	m_pf					=_pf;							//pointer to the physX particle system
	m_ps					= nullptr;
	m_particleMaxAge		= 8;							//maximum time in seconds that a particle can live for

	//initialize the buffer
	for(int index = 0;index<m_maxParticles;index++)
	{
		m_activeParticles[index].active = false;
	}
}

//constructor
ParticleEmitter::ParticleEmitter(int _maxParticles, PxVec3 _position, PxParticleSystem* _ps, float _releaseDelay)
{
	m_isFluid = false;

	m_releaseDelay			= _releaseDelay;
	m_maxParticles			= _maxParticles;				//maximum number of particles our emitter can handle
	
	//allocate an array
	m_activeParticles		= new Particle[m_maxParticles]; //array of particle structs
	m_time					= 0;							//time system has been running
	m_respawnTime			= 0;							//time for next respawn
	m_position				= _position;
	m_pf					= nullptr;
	m_ps					= _ps;							//pointer to the physX particle system
	m_particleMaxAge		= 8;							//maximum time in seconds that a particle can live for

	//initialize the buffer
	for (int index = 0; index < m_maxParticles; index++)
	{
		m_activeParticles[index].active = false;
		m_activeParticles[index].maxTime = 0;
	}
}

//destructure
ParticleEmitter::~ParticleEmitter()
{
	//remove all the active particles
	delete m_activeParticles;
}

void ParticleEmitter::SetStartVelocityRange(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	m_minVelocity.x = minX;
	m_minVelocity.y = minY;
	m_minVelocity.z = minZ;
	m_maxVelocity.x = maxX;
	m_maxVelocity.y = maxY;
	m_maxVelocity.z = maxZ;
}

//find the next free particle, mark it as used and return it's index.  If it can't allocate a particle: returns minus one
int ParticleEmitter::GetNextFreeParticle()
{
	//find particle, this is a very inefficient way to do this.  A better way would be to keep a list of free particles so we can quickly find the first free one
	for(int index=0;index<m_maxParticles;index++)
	{
		//when we find a particle which is free
		if(!m_activeParticles[index].active)
		{
			m_activeParticles[index].active = true; //mark it as not free
			m_activeParticles[index].maxTime = m_time+m_particleMaxAge;  //record when the particle was created so we know when to remove it
			return index;
		}
	}
	return -1; //returns minus if a particle was not allocated
}


//releast a particle from the system using it's index to ID it
void ParticleEmitter::ReleaseParticle(int index)
{
	if(index >= 0 && index < m_maxParticles)
		m_activeParticles[index].active = false;
}

//returns true if a particle age is greater than it's maximum allowed age
bool ParticleEmitter::TooOld(int index)
{
	if(index >= 0 && index < m_maxParticles && m_time > m_activeParticles[index].maxTime)
		return true;
	return false;
}

//add particle to PhysX System
bool ParticleEmitter::AddPhysXParticle(int particleIndex)
{

	//set up the buffers
	PxU32 myIndexBuffer[] = {(PxU32)particleIndex};
	PxVec3 startPos = m_position;
	PxVec3 startVel(0, 0, 0);
	//randomize starting velocity.
	float fT = (rand() % (RAND_MAX + 1)) / (float)RAND_MAX;
	startVel.x += m_minVelocity.x + (fT * (m_maxVelocity.x - m_minVelocity.x));
	fT = (rand() % (RAND_MAX + 1)) / (float)RAND_MAX;
	startVel.y += m_minVelocity.y + (fT * (m_maxVelocity.y - m_minVelocity.y));
	fT = (rand() % (RAND_MAX + 1)) / (float)RAND_MAX;
	startVel.z += m_minVelocity.z + (fT * (m_maxVelocity.z - m_minVelocity.z));

	//we can change starting position tos get different emitter shapes
	PxVec3 myPositionBuffer[] = {startPos};
	PxVec3 myVelocityBuffer[] =  {startVel};

	//reserve space for data
	PxParticleCreationData particleCreationData;
	//set up the data
	particleCreationData.numParticles = 1;  //spawn one particle at a time,  this is inefficient and we could improve this by passing in the list of particles.
	particleCreationData.indexBuffer = PxStrideIterator<const PxU32>(myIndexBuffer);
	particleCreationData.positionBuffer = PxStrideIterator<const PxVec3>(myPositionBuffer);
	particleCreationData.velocityBuffer = PxStrideIterator<const PxVec3>(myVelocityBuffer);
	// create particles in *PxParticleSystem* ps

	if(m_isFluid)
		return m_pf->createParticles(particleCreationData);
	else
		return m_ps->createParticles(particleCreationData);
}

//updateParticle
void ParticleEmitter::Update(float delta)
{
	//tick the emitter
	m_time += delta;
	m_respawnTime+= delta;
	int numberSpawn = 0;
	//if respawn time is greater than our release delay then we spawn at least one particle so work out how many to spawn
	if(m_respawnTime>m_releaseDelay)
	{
		numberSpawn = (int)(m_respawnTime/m_releaseDelay);
		m_respawnTime -= (numberSpawn * m_releaseDelay);
	}
	// spawn the required number of particles 
	for(int count = 0;count < numberSpawn;count++)
	{
		//get the next free particle
		int particleIndex = GetNextFreeParticle();
		if(particleIndex >=0)
		{
			//if we got a particle ID then spawn it
			AddPhysXParticle(particleIndex);
		}
	}


	//check to see if we need to release particles because they are either too old or have hit the particle sink
	//lock the particle buffer so we can work on it and get a pointer to read data
	PxParticleReadData* rd;

	if (m_isFluid)
		rd = m_pf->lockParticleReadData();
	else
		rd = m_ps->lockParticleReadData();

	// access particle data from PxParticleReadData was OK
	if (rd)
	{
		vector<PxU32> particlesToRemove; //we need to build a list of particles to remove so we can do it all in one go
		PxStrideIterator<const PxParticleFlags> flagsIt(rd->flagsBuffer);

		for (unsigned i = 0; i < rd->validParticleRange; ++i, ++flagsIt)
		{
			if (*flagsIt & PxParticleFlag::eVALID)
			{
				//if particle is either too old or has hit the sink then mark it for removal.  We can't remove it here because we buffer is locked
				if (*flagsIt & PxParticleFlag::eCOLLISION_WITH_DRAIN || TooOld(i))
				{
					//mark our local copy of the particle free
					ReleaseParticle(i);
					//add to our list of particles to remove
					particlesToRemove.push_back(i);
				}
			}
		}
		// return ownership of the buffers back to the SDK
		rd->unlock();
		//if we have particles to release then pass the particles to remove to PhysX so it can release them
		if(particlesToRemove.size()>0)
		{
			//create a buffer of particle indicies which we are going to remove
			PxStrideIterator<const PxU32> indexBuffer(&particlesToRemove[0]);
			//free particles from the physics system
			if (m_isFluid)
				m_pf->releaseParticles(particlesToRemove.size(), indexBuffer);
			else
				m_ps->releaseParticles(particlesToRemove.size(), indexBuffer);
			
		}
	}
}

//simple routine to render our particles
void ParticleEmitter::RenderParticles()
{
	// lock SDK buffers of *PxParticleSystem* ps for reading

	PxParticleFluidReadData * fd;
	PxParticleReadData* rd;
	if (m_isFluid)
	{
		fd = m_pf->lockParticleFluidReadData();
		// access particle data from PxParticleReadData
		if (fd)
		{
			PxStrideIterator<const PxParticleFlags> flagsIt(fd->flagsBuffer);
			PxStrideIterator<const PxVec3> positionIt(fd->positionBuffer);
			PxStrideIterator<const PxF32> densityIt(fd->densityBuffer);
			for (unsigned i = 0; i < fd->validParticleRange; ++i, ++flagsIt, ++positionIt, ++densityIt)
			{
				if (*flagsIt & PxParticleFlag::eVALID)
				{
					//density tells us how many neighbours a particle has.  
					//If it has a density of 0 it has no neighbours, 1 is maximum neighbouts
					//we can use this to decide if the particle is seperate or part of a larger body of fluid
					glm::vec3 pos(positionIt->x, positionIt->y, positionIt->z);
					Gizmos::addSphere(pos, .5,5,5, glm::vec4(0, 0, 0.5, 1));
				}
			}
			// return ownership of the buffers back to the SDK
			fd->unlock();
		}
	}
	else
	{
		rd = m_ps->lockParticleReadData();
		if (rd)
		{
			PxStrideIterator<const PxParticleFlags> flagsIt(rd->flagsBuffer);
			PxStrideIterator<const PxVec3> positionIt(rd->positionBuffer);

			for (unsigned i = 0; i < rd->validParticleRange; ++i, ++flagsIt, ++positionIt)
			{
				if (*flagsIt & PxParticleFlag::eVALID)
				{
					//convert physx vector to a glm vec3
					glm::vec3 pos(positionIt->x, positionIt->y, positionIt->z);
					//use a gizmo box to visualize particle.  This would be much better done using a facing quad preferably done using the geometry shader
					Gizmos::addAABBFilled(pos, glm::vec3(.1, .1, .1), glm::vec4(1, 0, 1, 1));
				}
			}
			// return ownership of the buffers back to the SDK
			rd->unlock();
		}
	}


}