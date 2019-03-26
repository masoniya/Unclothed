#include "PointMass.h"



PointMass::PointMass()
{
	init(1.0f, glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, 0));

}

PointMass::PointMass(float mass, glm::vec3 pos)
{
	init(mass, pos, glm::vec3(0, 0, 0));

}


void PointMass::init(float mass, glm::vec3 position, glm::vec3 velocity)
{
	this->mass = mass;

	this->position = position;
	this->velocity = velocity;

}



float PointMass::getMass()
{
	return this->mass;
}
glm::vec3 PointMass::getPosition()
{
	return position;
}
glm::vec3 PointMass::getVelocity()
{
	return velocity;
}
glm::vec3 PointMass::getAcceleration()
{

	return forceAccum / mass;
}
void PointMass::setPosition(glm::vec3 pos)
{
	this->position = pos;

}
void PointMass::setMass(float mass)
{
	this->mass = mass;

}
void PointMass::addForce(const glm::vec3 &force)
{
	forceAccum += force;

}

void PointMass::clearAccum()
{
	forceAccum = glm::vec3(0, 0, 0);
}

void PointMass::printPos()
{
	std::cout << position.x <<" "<< position.y << "\n";

}
