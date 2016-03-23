#pragma once

#include <vector>

class GameObject;

class EntityManager
{
public:
	static EntityManager* GetInstance();
	~EntityManager();
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	GameObject* CreateEntity();

private:
	EntityManager();
	static EntityManager* m_instance;

	std::vector<GameObject> m_entitys;
};