#include "Spring.h"


Spring::Spring(float k, float d, PointMass * particle1, PointMass * particle2,float maxRate)
{
	init(k, d, particle1, particle2,maxRate);

}


float Spring::getRestLength()
{
	return this->restLength;
}

float Spring::getCurrentLength()
{
	glm::vec3 diff = pointMasses[0]->getPosition() - pointMasses[1]->getPosition();
	return glm::length(diff);
}

void Spring::setMasterPoint(PointMass * master)
{
	if((*pointMasses[0])==(*master)){
		masterPoint = 0;
	}
	else {
		masterPoint = 1;
	}

}

//performance critical function (optimize to shit)
void Spring::applyForce()
{

	glm::vec3 posDiff = pointMasses[0]->getPosition() - pointMasses[1]->getPosition();

	glm::vec3 velDiff = pointMasses[0]->getVelocity() - pointMasses[1]->getVelocity();
	
	//float length = getCurrentLength();
	float length = glm::length(posDiff); //~ 10fps faster

	glm::vec3 dir = glm::normalize(posDiff);

	glm::vec3 force = -(springConst * (length - restLength)) * dir - (velDiff * dampingConst);
	
	

	pointMasses[0]->addForce(force);
	pointMasses[1]->addForce(-force);

}

void Spring::adjust()
{
	PointMass* master = pointMasses[masterPoint];
	PointMass* other = pointMasses[(masterPoint + 1) % 2];

	float currentLength = getCurrentLength();
	float deformRate =  ( (currentLength - restLength) / restLength)*100;

	if (deformRate > maxDeformRate) {

		glm::vec3 pos = master->getPosition() - restLength* (1 + maxDeformRate / 100) * (master->getPosition() - other->getPosition()) / currentLength;
		other->setPosition(pos);
	}

}

void Spring::init(float k, float d,  PointMass * particle1, PointMass * particle2,float maxRate)
{

	this->pointMasses = new PointMass*[2];
	this->pointMasses[0] = particle1;
	this->pointMasses[1] = particle2;

	this->springConst = k;
	this->dampingConst = d;

	this->masterPoint = 0;
	this->maxDeformRate = maxRate;
	

	this->restLength = glm::length(particle1->getPosition() - particle2->getPosition());
}
