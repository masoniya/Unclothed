#include "PhysicsEngine.h"
#include "Cloth.h"
#include "GravitationalForce.h"
#include "DragForce.h"


PhysicsEngine::PhysicsEngine(Render* renderer)
{
	this->renderer = renderer;

	timeStep = 1.0f / 60.0f;
	timeAccumulator = 0.0f;

	//initialize forces 
	GravitationalForce* gravity = new GravitationalForce(glm::vec3(0, -1.8f, 0));
	DragForce * drag = new DragForce(0.4f);
	
	this->externalForces.push_back(gravity);
	this->externalForces.push_back(drag);

	//initialize objects
	width = 25;
	height = 25;

	Cloth* cloth = new Cloth(glm::vec3(-0.5f, 0.5f, -0.5f), width, height, 1.0f, 1.0f, 1.0f);

	this->physicalObjects.push_back(cloth);
	gravity->addPhysicalObject(cloth);
	drag->addPhysicalObject(cloth);
	
	int size = (width - 1) * (height - 1) * 8 * 6;
	this->renderer->initcloth(cloth->getVertexData(), size);
	
}

void PhysicsEngine::updatePhyics(float deltaTime)
{
	this->timeAccumulator += deltaTime;

	while (timeAccumulator >= timeStep) {
		
		//apply the external forces (~ 0.2ms)
		for (ForceGenerator* forceGenerator : externalForces) {
			forceGenerator->applyForce();
		}

		//call update method on each body which calculates the internal forces and then integrates (~ 4.5ms)
		for (DeformableBody* object : physicalObjects) {
			object->update(timeStep);
		}

		timeAccumulator -= timeStep;
	}
	//(~ 2ms)
	this->updateRenderer();

}

void PhysicsEngine::addPhysicalObject(DeformableBody * physicalObject)
{
	physicalObjects.push_back(physicalObject);
}

void PhysicsEngine::addExternalForce(ForceGenerator * externalForce)
{
	externalForces.push_back(externalForce);
}

void PhysicsEngine::updateRenderer()
{
	Cloth* cloth = (Cloth*)physicalObjects[0];

	this->renderer->updatecloth(cloth->getVertexData(), (width - 1) * (height - 1) * 8 * 6);
}
