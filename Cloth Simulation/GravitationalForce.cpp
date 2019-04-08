#include "GravitationalForce.h"

GravitationalForce::GravitationalForce()
{
	gravityAcceleration = glm::vec3(0, -0.00001f, 0);
}

GravitationalForce::GravitationalForce(glm::vec3 grav)
{
	gravityAcceleration = glm::vec3(grav);
}


void GravitationalForce::applyForce()
{
	for (Gravity* object : physicalObjects) {

		object->applyGravity(gravityAcceleration);
	}

}

void GravitationalForce::addPhysicalObject(Gravity* body)
{
	physicalObjects.push_back(body);
}
