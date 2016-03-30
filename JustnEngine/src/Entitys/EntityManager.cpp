#include "Entitys\EntityManager.h"
#include "Entitys\GameObject.h"

EntityManager* EntityManager::m_instance = new EntityManager();

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

EntityManager * EntityManager::GetInstance()
{
	if (!m_instance)
		m_instance = new EntityManager();

	return m_instance;
};

GameObject* EntityManager::CreateEntity()
{
	m_entitys.emplace_back();
	return &m_entitys.back();
}

GLuint EntityManager::GetEntityCount()
{ 
	return m_entitys.size();
}