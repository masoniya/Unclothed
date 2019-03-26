#include "SemiImpEuler.h"



SemiImpEuler::SemiImpEuler()
{

}




void SemiImpEuler::solve(float deltaTime)
{
	for (PointMass* point : points) {

		glm::vec3 velNew = point->getVelocity() + point->getAcceleration()*deltaTime;
		glm::vec3 posNew = point->getPosition() + velNew * deltaTime;

		point->setPosition(posNew);
		
		
	}
	

}

