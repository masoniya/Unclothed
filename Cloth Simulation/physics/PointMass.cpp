#include "PointMass.h"



PointMass::PointMass()
{
	init(1.0f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

}

//might add a constructer with arguments here later

PointMass::~PointMass()
{

}

void PointMass::init(float mass, glm::vec3 position, glm::vec3 velocity)
{
	this->mass = mass;

	this->position = position;
	this->velocity = velocity;

}

//later on will pass along an integrator to update the velocity and position according to an algorithm
void PointMass::update(float deltaTime)
{



}
float PointMass::getMass()
{
	return this->mass;
}
void PointMass::addForce(const glm::vec3 &force)
{
	forceAccum += force;

}

void PointMass::clearAccum()
{
	forceAccum = glm::vec3(0, 0, 0);
}
