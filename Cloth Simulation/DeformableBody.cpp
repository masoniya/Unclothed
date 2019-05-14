#define _USE_MATH_DEFINES
#include "DeformableBody.h"
#include <glfw/glfw3.h>
#include <cmath>

void DeformableBody::applyGravity(glm::vec3 gravityAcceleration)
{
	for (PointMass* point : points) {
		point->addForce(point->getMass() * gravityAcceleration);
	}
}

void DeformableBody::applyDrag(float damp)
{
	for (PointMass* point : points) {
		point->addForce(-point->getVelocity() * damp);
	}
}

void DeformableBody::applyWind()
{
	SimplexNoise* noise = new SimplexNoise();
	float time = glfwGetTime();
	timer += 0.004f;

	float length = 4.0f;
	for (PointMass* point : points) {

		glm::vec3 pos = point->getPosition();

		float value = noise->noise(pos.x , pos.z, time);
		float value2 = noise->noise(pos.x+1000 , pos.z +1000, time);
	
		float val = (value + 1) / 2;
		float val2 = (value2 + 1) / 2;


		float xValue = cos(val*M_PI*2);
		float yValue = sin(val*M_PI*2);

		float lengthvalue = length*val2;
		float val3 =  sin(val*M_PI*2);
		glm::vec3 force = lengthvalue*glm::vec3(val,0.0f, val) ;
		//glm::vec3 force =val3* glm::vec3(6.0f, 0.0f, 2.0f);
		point->addForce(force);

	}

}

void DeformableBody::collide(RigidShape * shape)
{
	glm::vec3 Q;
	for (PointMass* point : points) {

		glm::vec3 p0 = point->prevPostion;
		glm::vec3 p1 = point->getPosition();
		glm::vec3 vel = point->getVelocity();


		glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);



		if (shape->intersectPoint(p1, dir)) {

			point->position = shape->center + shape->radius*dir;
			glm::vec3 Vn = glm::dot(dir, vel) * dir;
			glm::vec3 Vt = vel - Vn;
			//Vt =glm::normalize(Vt);
			point->setVelocity(/*0.2f*Vt*/ - Vn);

			//point->collides = true;



			/*glm::vec3  force = Vn;
			point->addForce(force);*/

			//std::cout << "intersection";
		/*}*/


		/*for (Triangle* triangle : shape->triangles) {


			if (triangle->intersect(p0, p1,Q)) {*/


			/*glm::vec3 Vn = glm::dot(triangle->normal, vel)*vel;
			glm::vec3 Vt = vel - Vn;

			glm::vec3  force = triangle->normal*2.0f;
			point->addForce(force);
			point->setVelocity(Vt - 0.4f*Vn);
			point->setImmovable();
			point->setPosition(p0);*/
			//std::cout << "hey";

			//point->position = Q;

		}
		/*else {
			std::cout << "nope";
		}*/


		/*}*/




	/*}*/




	}
}
