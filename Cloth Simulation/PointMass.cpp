#include "PointMass.h"


PointMass::PointMass()
{
	init(1.0f, glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, 0), false);
}

PointMass::PointMass(float mass, glm::vec3 pos, bool immovable)
{
	init(mass, pos, glm::vec3(0, 0, 0), immovable);
}


void PointMass::init(float mass, glm::vec3 position, glm::vec3 velocity, bool immovable)
{
	this->mass = mass;
	this->immovable = immovable;
	this->position = position;
	this->velocity = velocity;
	this->forceAccum = glm::vec3(0.0f, 0.0f, 0.0f);
}

float PointMass::getMass()
{
	return mass;
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

glm::vec3 PointMass::getNormal()
{
	return pointNormal;
}

void PointMass::setPosition(glm::vec3 pos)
{
	if (!immovable) {
		position = pos;
	}
}

void PointMass::setVelocity(glm::vec3 vel)
{
	if (!immovable) {
		velocity = vel;
	}
}

void PointMass::setMass(float mass)
{
	this->mass = mass;
}

void PointMass::setImmovable()
{
	immovable = true;
}

//add a face normal to the normal accumulator
void PointMass::addNormal(glm::vec3 normal)
{
	normalAccum.push_back(normal);
}

//calculate average normal then clear the accumulator
void PointMass::calculatePointNormal()
{
	glm::vec3 totalNormal(0.0f);
	for (glm::vec3 normal : normalAccum) {
		totalNormal += normal;
	}
	pointNormal = glm::normalize((1.0f / normalAccum.size()) * totalNormal);
	normalAccum.clear();
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
	std::cout << position.x << " " << position.y << "\n";
}
