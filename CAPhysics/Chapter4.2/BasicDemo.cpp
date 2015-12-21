#include "BasicDemo.h"

void BasicDemo::InitializePhysics() {
	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	// create our scene's physics objects
	CreateObjects();
}

void BasicDemo::ShutdownPhysics() {
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void BasicDemo::CreateObjects() {
	// create a ground plane
	CreateGameObject(new btBoxShape(btVector3(1,50,50)), 0, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
	// create our original red box
	CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(-0.5f, 10.0f, 0.0f));
	CreateGameObject(new btBoxShape(btVector3(1.5,0.1,1.0)), 1.0, btVector3(1.0f, 0.2f, 0.2f), btVector3(0.0f, 0.0f, 0.0f));
	// create a second box
	CreateGameObject(new btBoxShape(btVector3(1.5,0.1,1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(1.0f, 0.0f, 0.0f));
	CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(2.0f, 0.0f, -0.2f));
	CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(3.0f, 0.0f, -0.4f));

	// Set up dominos using some calculation like Sin/Cos/Tan to make a huge map of dominos
	// TODO: Change camera angle to get a better view of the dominos (david)
	for (int i = 0; i < 10; i++)
	{
		CreateGameObject(new btBoxShape(btVector3(1.5, 0.1, 1.0)), 1.0, btVector3(2.0f, 0.2f, 0.8f), btVector3((float)i/* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)-i /* Depth */));
	}
	

}
