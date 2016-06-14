#include "Components\PlayerController.h"
#include "Components\Transform.h"
#include "Entitys\GameObject.h"
#include "Physics\PhysXManager.h"

#include "GLFW\glfw3.h"

#include "all_includes.h"

PlayerController::PlayerController()
{
	m_physXManager = PhysXManager::GetInstance();
	m_currentWindow = glfwGetCurrentContext();
}

PlayerController::~PlayerController()
{

}

void PlayerController::Update(float deltaTime)
{
	bool onGround; //set to true if we are on the ground
	float movementSpeed = 10.0f; //forward and back movement speed
	float rotationSpeed = 1.0f; //turn speed
	

	//check if we have a contact normal. if y is greater than .3 we assume this is solid ground.This is a rather primitive way to do this.Can you do better ?
	if (myHitReport->GetPlayerContactNormal().y > 0.3f)
	{
		m_yVelocity = -0.1f;
		onGround = true;
	}
	else
	{
		m_yVelocity += m_gravity * deltaTime;
		onGround = false;
	}

	myHitReport->ClearPlayerContactNormal();

	const PxVec3 up(0, 1, 0);
	//scan the keys and set up our intended velocity based on a global transform
	PxVec3 velocity(0, m_yVelocity, 0);
	if (glfwGetKey(m_currentWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		velocity.x -= movementSpeed*deltaTime;
	}
	if (glfwGetKey(m_currentWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		velocity.x += movementSpeed*deltaTime;
	}
	//To do.. add code to control z movement and jumping
	float minDistance = 0.001f;
	PxControllerFilters filter;
	//make controls relative to player facing
	PxQuat rotation(m_rotation, PxVec3(0, 1, 0));
	//PxVec3 velocity(0, m_yVelocity, 0);
	//move the controller
	m_playerController->move(rotation.rotate(velocity), minDistance, deltaTime,	filter);
}

void PlayerController::Start()
{
	if(GetGameObject()->GetComponent<Transform>() != nullptr)
		m_myTransform = GetGameObject()->GetComponent<Transform>();
	vec3 pos = m_myTransform->GetPosition();

	//ControllerHitRe
	myHitReport = new MyControllerHitReport();
	//describe our controller...
	PxCapsuleControllerDesc desc;
	desc.height = 1.6f;
	desc.radius = 0.4f;
	desc.position.set(0, 0, 0);
	desc.material = m_physXMaterial;
	desc.reportCallback = myHitReport; //connect it to our collision detection routine
	desc.density = 10; 	//create the layer controller
	m_playerController = m_physXManager->GetControllerManager()->createController(desc);
	m_playerController->setPosition(PxExtendedVec3(pos.x, pos.y, pos.z)); //set up some variables to control our player with
	m_yVelocity = 0; //initialize character velocity
	m_rotation = 0; //and rotation
	m_gravity = -0.5f; //set up the player gravity
	myHitReport->ClearPlayerContactNormal(); //initialize the contact normal (what we are in contact with)
}

void MyControllerHitReport::onShapeHit(const PxControllerShapeHit &hit)
{
	//gets a reference to a structure which tells us what has been hit and where
	//get the acter from the shape we hit
	PxRigidActor* actor = hit.shape->getActor();
	//get the normal of the thing we hit and store it so the player controller can respond correctly 
	_playerContactNormal = hit.worldNormal;
	//try to cast to a dynamic actor
	PxRigidDynamic* myActor = actor->is<PxRigidDynamic>();
	if (myActor)
	{
		//this is where we can apply forces to things we hit
		
	}
}