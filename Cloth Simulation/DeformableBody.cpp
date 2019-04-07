#include "DeformableBody.h"


void DeformableBody::applyGravity(glm::vec3 gravityAcceleration)
{
	for (PointMass* point : points) {
		point->addForce(point->getMass()*gravityAcceleration);
	}

}

void DeformableBody::applyDrag(float damp)
{
	for (PointMass* point : points) {
		point->addForce(-point->getVelocity()*damp);
	}
}




