#pragma once

#include <glm/gtc/matrix_transform.hpp>




class Triangle
{
public:
	Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	
	glm::vec3 normal;
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;


	glm::vec3 getEdge1();
	glm::vec3 getEdge2();
	glm::vec3 getEdge3();

	bool intersect(glm::vec3 p0, glm::vec3 p1,glm::vec3 &Q);
	bool intersect2(glm::vec3 p0, glm::vec3 p1, glm::vec3 &Q);
	bool intersect3(glm::vec3 p0, glm::vec3 p1, glm::vec3 &Q);
	bool pointInTriangle(glm::vec3 p);
	bool pointIntersectPlane(glm::vec3 p, glm::vec3 dir , float &t);
	void update(glm::mat4 transform);

private:
	
	
};

