#include "Gravity.h"

Gravity::Gravity()
{
	gravity = glm::vec3(0, -9.8f, 0);
}

Gravity::Gravity(glm::vec3 grav)
{
	gravity = glm::vec3(grav);
}




void Gravity::applyForce()
{
	for (PointMass* pointMass : points) {

		pointMass->addForce(gravity* pointMass->getMass());
	}

}


