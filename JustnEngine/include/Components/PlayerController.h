#pragma once
#include "Components\Collider.h"

#include <PxPhysicsAPI.h>
#include <PxScene.h>

using namespace physx;

class PhysXManager;
class GLFWwindow;

class MyControllerHitReport : public PxUserControllerHitReport
{
public:
	//overload the onShapeHit function
	virtual void onShapeHit(const PxControllerShapeHit &hit);
	//other collision functions which we must overload //these handle collision	with other controllers and hitting obstacles
	virtual void onControllerHit(const PxControllersHit &hit) {};
	//Called when current controller hits another controller. More...
	virtual void onObstacleHit(const PxControllerObstacleHit &hit) {};
	//Called when current controller hits a user-defined obstacl
	MyControllerHitReport() :PxUserControllerHitReport() {};
	PxVec3 GetPlayerContactNormal() { return _playerContactNormal; };
	void ClearPlayerContactNormal() { _playerContactNormal = PxVec3(0, 0, 0); };
	PxVec3 _playerContactNormal;
};

class PlayerController : public Component<Transform>
{
public:
	PlayerController();
	~PlayerController();

	void Update() override {};
	void Update(float deltaTime);


	void Start();

private:

	Transform* m_myTransform;

	PhysXManager* m_physXManager;
	PxMaterial* m_physXMaterial;
	PxController* m_playerController;
	MyControllerHitReport* myHitReport;

	GLFWwindow* m_currentWindow;

	float m_yVelocity;
	float m_rotation;
	float m_gravity;

};

