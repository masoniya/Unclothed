#include <glfw/glfw3.h>

#include "PhysicsEngine.h"
#include "Cloth.h"
#include "GravitationalForce.h"
#include "DragForce.h"
#include "InputManager.h"


extern InputManager *activeInputManager;

PhysicsEngine::PhysicsEngine(Render* renderer)
{
	this->renderer = renderer;

	timeStep = 1.0f / 60.0f;
	timeAccumulator = 0.0f;

	//initialize forces 
	GravitationalForce* gravity = new GravitationalForce(glm::vec3(0, -1.8f, 0));
	DragForce * drag = new DragForce(0.5f);

	
	this->externalForces.push_back(gravity);
	this->externalForces.push_back(drag);


	//initialize objects
	width = 22;
	height = 22;

	Cloth* cloth = new Cloth(glm::vec3(-0.5f, 0.5f, -0.5f), width, height, 1.0f, 1.0f, 1.0f);
	activeInputManager->registerKeyboardInput(cloth);

	this->physicalObjects.push_back(cloth);
	gravity->addPhysicalObject(cloth);
	drag->addPhysicalObject(cloth);
	
	int size = (width-1)*(height-1)  * 8 * 6;
	this->renderer->initcloth(cloth->getVertexData(), size);
	
}

void PhysicsEngine::updatePhyics(float deltaTime)
{
	static int iterations = 0;
	static float fuckYouTimeAccumulator;
	

	this->timeAccumulator += deltaTime;

	while (timeAccumulator >= timeStep) {
		iterations++;

		//apply the external forces
		for (ForceGenerator* forceGenerator : externalForces) {
			forceGenerator->applyForce();
		}

		//call update method on each body which calculates the internal forces and then integrates
		for (DeformableBody* object : physicalObjects) {
			object->update(timeStep);
			
		}

		fuckYouTimeAccumulator += timeStep;
		timeAccumulator -= timeStep;


	}

	static bool printed = false;
	if (!printed && glfwGetTime() > 5.0f) {
		//std::cout << "iterations : " << iterations << " , Time elapsed : " << fuckYouTimeAccumulator << std::endl;
		printed = true;
	}

	this->updateRenderer();

}

void PhysicsEngine::updateRenderer()
{
	Cloth* cloth = (Cloth*)physicalObjects[0];

	this->renderer->updatecloth(cloth->getVertexData(), (width - 1)*(height - 1) * 8 * 6);

}
