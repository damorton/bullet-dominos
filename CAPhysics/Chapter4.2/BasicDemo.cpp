#include "BasicDemo.h"
#include <math.h>
#include <cstdlib>
#include <ctime>

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

	// Random number seed
	srand(static_cast <unsigned> (time(0)));

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
		
	// Create domino patterns using enum in BasicDemo.h
	CreatePattern(110, SPIRAL);
}

float BasicDemo::RandomColor(float maxValue)
{
	float randomColor = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / maxValue));
	return randomColor;
}

void BasicDemo::CreatePattern(int maxPoints, int type)
{
	float colorRed = 0.0f;
	float colorGreen = 0.0f;
	float colorBlue = 0.0f;

	float dominoHeight = 2.0f;

	if (type == SPIRAL)
	{
		// create spiral dominos
		float x = 0;
		float z = 0;
		float angle = 0.0f;
		int a = 2, b = 2;
		float previousX = 0.0f;
		float previousZ = 0.0f;
		

		

		// Create blue box to hit first domino
		CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(2.0f, 8.0f, 0.0f));

		for (int i = 2; i < maxPoints; i++)
		{
			colorRed = RandomColor(2.0f);
			colorGreen = RandomColor(2.0f);
			colorBlue = RandomColor(2.0f);

			if (i % 30 == 0) dominoHeight++;

			angle = 0.15 * i;
			x = (a + b * angle) * cos(angle);
			z = (a + b * angle) * sin(angle);

			GameObject* temp = CreateGameObject(new btBoxShape(btVector3(dominoHeight, 1.5f, 0.1f)), 1.0, btVector3(colorRed, colorGreen, colorBlue), btVector3((float)x /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)z /* Depth */));

			float dirX = -(a + b * angle) * sin(angle) + (b * cos(angle));
			float dirZ = (a + b * angle) * cos(angle) + (b * sin(angle));
			float newAngle = atan2(dirX, dirZ);
			printf("dirX: %f - dirZ: %f - angle: %f\n", dirX, dirZ, newAngle);
			temp->setRotationYaw(newAngle);
			
			previousX = x;
			previousZ = z;
		}
	}
	else if (type == LOGARITHMIC)
	{
		// Log pattern
	}
	else if (type == WAVE)
	{
		float waveX = 0.0f;
		float waveY = 0.0f;
		float first = 0.0f, second = 1.0f, next;
				
		// Create blue box to hit first domino
		CreateGameObject(new btBoxShape(btVector3(1, 1, 1)), 1.0, btVector3(0.0f, 0.2f, 0.8f), btVector3(0.0f, 8.0f, 0.0f));

		// X Axis
		for (waveX = -50; waveX < maxPoints; waveX++)
		{
			colorRed = RandomColor(2.0f);
			colorGreen = RandomColor(2.0f);
			colorBlue = RandomColor(2.0f);

			dominoHeight += 0.1f;

			if (waveX <= 1)
				next = waveX;
			else
			{
				next = first + second;
				first = second;
				second = next;
			}

			waveY = sin(waveX) - 0.5*waveX;

			CreateGameObject(new btBoxShape(btVector3(dominoHeight, 0.1, 1.5)), 1.0, btVector3(colorRed, colorGreen, colorBlue), btVector3((float)waveX /* X Axis left or right */, 0.0f /* Domino sitting on the ground */, (float)waveY /* Depth */));
		}
	}
}
