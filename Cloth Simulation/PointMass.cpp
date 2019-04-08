#include "PointMass.h"


PointMass::PointMass()
{
	init(1.0f, glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, 0),false);

}

PointMass::PointMass(float mass, glm::vec3 pos,bool immovable)
{
	init(mass, pos, glm::vec3(0, 0, 0),immovable);

}


void PointMass::init(float mass, glm::vec3 position, glm::vec3 velocity,bool immovable)
{
	this->mass = mass;
	this->immovable = immovable;
	this->position = position;
	this->velocity = velocity;
	this->forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);

}

float PointMass::getMass()
{
	return this->mass;
}

glm::vec3 PointMass::getPosition()
{
	return this->position;
}

glm::vec3 PointMass::getVelocity()
{
	return this->velocity;
}

glm::vec3 PointMass::getAcceleration()
{

	return this->forceAccum / mass;
}

void PointMass::setPosition(glm::vec3 pos)
{
	if (!immovable) {
		this->position = pos;
	}
}

void PointMass::setVelocity(glm::vec3 vel)
{
	if (!immovable) {
		this->velocity = vel;
	}
}

void PointMass::setMass(float mass)
{
	this->mass = mass;

}

void PointMass::setImmovable()
{
	this->immovable = true;
}

void PointMass::addForce(const glm::vec3 &force)
{
	this->forceAccum += force;

}

void PointMass::clearAccum()
{
	this->forceAccum = glm::vec3(0, 0, 0);
}

void PointMass::printPos()
{
	std::cout << position.x <<" "<< position.y << "\n";

}
