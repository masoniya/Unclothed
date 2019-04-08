#include "Spring.h"


Spring::Spring(float k, float d, PointMass * particle1, PointMass * particle2)
{
	init(k, d, particle1, particle2);

}
Spring::Spring()
{

}


float Spring::getRestLength()
{
	return this->restLength;
}

float Spring::getCurrentLength()
{
	glm::vec3 diff = pointMass1->getPosition() - pointMass2->getPosition();
	return glm::length(diff);

}

void Spring::applyForce()
{

	glm::vec3 posDiff = pointMass1->getPosition() - pointMass2->getPosition();

	glm::vec3 velDiff = pointMass1->getVelocity() - pointMass2->getVelocity();
	

	float length = getCurrentLength();


	glm::vec3 dir = glm::normalize(posDiff);


	glm::vec3 force = -(springConst * (length - restLength) ) *dir - (velDiff * dampingConst);
	
	/*+dampingConst * velDiff*/

	pointMass1->addForce(force);
	pointMass2->addForce(-force);

}

void Spring::init(float k, float d,  PointMass * particle1, PointMass * particle2)
{
	this->springConst = k;
	this->dampingConst = d;

	this->pointMass1 = particle1;

	this->pointMass2 = particle2;

	this->restLength = glm::length(particle1->getPosition() - particle2->getPosition());

}
