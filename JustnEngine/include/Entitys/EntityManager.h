#pragma once

#include <vector>
#include <gl_core_4_4.h>
#include "Entitys\GameObject.h"

class GameObject;

class EntityManager
{
public:
	static EntityManager* GetInstance();
	~EntityManager();
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	GameObject* CreateEntity();
	std::vector<GameObject>* GetEntitys() { return &m_entitys; };
	GLuint GetEntityCount();

private:
	EntityManager();
	static EntityManager* m_instance;

	std::vector<GameObject> m_entitys;
};