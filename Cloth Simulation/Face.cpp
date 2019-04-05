#include "Face.h"



Face::Face(PointMass* point1, PointMass* point2, PointMass * point3)
{
	init(point1, point2, point3);

}




float Face::getArea()
{
	glm::vec3 diff1 = point2->getPosition() - point1->getPosition();
	glm::vec3 diff2 = point3->getPosition() - point1->getPosition();

	glm::vec3 cross = glm::cross(diff1, diff2);

	return (float)cross.length();


}

void Face::init(PointMass* point1, PointMass* point2, PointMass * point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;

	calcNormal();

}

void Face::calcNormal()
{
	glm::vec3 diff1 = point2->getPosition() - point1->getPosition();
	glm::vec3 diff2 = point3->getPosition() - point1->getPosition();

	glm::vec3 cross = glm::cross(diff1, diff2);

	this->normal = cross / (float)cross.length();
}

glm::vec3 Face::calcNormal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	glm::vec3 diff1 = point2 - point1;
	glm::vec3 diff2 = point3 - point1;

	glm::vec3 cross = glm::cross(diff1, diff2);

	return cross / glm::length(cross);

}


