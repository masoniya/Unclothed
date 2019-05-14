#include "Triangle.h"




using namespace std;



Triangle::Triangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;

	


	this->normal = glm::normalize(glm::cross(getEdge1(), getEdge2()));

}

glm::vec3 Triangle::getEdge1()
{
	return  glm::normalize(point1 - point2);
}

glm::vec3 Triangle::getEdge2()
{
	return  glm::normalize(point1 - point3);
}

glm::vec3 Triangle::getEdge3()
{
	return glm::normalize(point2 - point3);
}

bool Triangle::intersect(glm::vec3 p0 , glm::vec3 p1, glm::vec3 &Q)
{
	/*glm::vec3 diff1 = p0 - this->point1;
	glm::vec3 diff2 = p1 - this->point1;

	float dot1 = glm::dot(diff1, this->normal);
	float dot2 = glm::dot(diff2, this->normal);

	if (dot1*dot2 < 0.0f) {
		return false;
	}*/

	glm::vec3 raydir = p1 - p0;
	float t;
	if (!pointIntersectPlane(p0, raydir, t)) {
		return false;
	}
	 Q = p0 + t * raydir;

	if (!pointInTriangle(Q)) {
		return false;
	}
	
	return true;
}

bool Triangle::intersect2(glm::vec3 p0, glm::vec3 p1, glm::vec3 & Q)
{
	glm::vec3 c = (p1 - p0)*(1.0f / 60.0f);
	
	if (glm::dot(c, this->normal) > 0.0f) {
		return false;
	}
	float t = (glm::dot(this->normal, this->point1 - p0) / glm::dot(this->normal, c));
	if (!(t >= 0.0f && t <= 1.0f)) {
		return false;
	}
	Q = p0 + c * t;

	if (!pointInTriangle(Q)) {
		return false;
	}

	return true;
}

bool Triangle::intersect3(glm::vec3 p0, glm::vec3 p1, glm::vec3 &Q)
{
	float da = glm::dot(this->normal, p0 - this->point1);
	float db = glm::dot(this->normal, p1 - this->point1);

	if (db*da >= 0.0f) {
		return false;
	}
	Q = (da*p1 - (db * p0) ) / (da - db);

	glm::vec3 p3p1 = (this->point3 - this->point1);
	glm::vec3 p2p3 = (this->point2 - this->point3);
	glm::vec3 p1p2 = (this->point1 - this->point2);

	glm::vec3 Qp1 = (Q - this->point1);
	glm::vec3 Qp3 = (Q - this->point3);
	glm::vec3 Qp2 = (Q - this->point2);


	if (glm::dot(Qp1, glm::cross(p3p1, this->normal)) <= 0.0f) {
		return false;
	}
	if (glm::dot(Qp3, glm::cross(p2p3, this->normal)) <= 0.0f) {
		return false;
	}
	if (glm::dot(Qp2, glm::cross(p1p2, this->normal)) <= 0.0f) {
		return false;
	}

	return true;
}

bool Triangle::pointInTriangle(glm::vec3 p)
{
	//translate points to the p as new origin
	glm::vec3 a = this->point1 - p;
	glm::vec3 b = this->point2 - p;
	glm::vec3 c = this->point3 - p;

	glm::vec3 u = glm::cross(b, c);
	glm::vec3 v = glm::cross(c, a);


	if (glm::dot(u, v) < 0.0f) {
		return false;
	}

	glm::vec3 w = glm::cross(a, b);

	if (glm::dot(u, w) < 0.0f) {
		return false;
	}

	
	/*float ab = glm::dot(a, b);
	float ac = glm::dot(c, a);
	float bc = glm::dot(b,c);
	
	float cc = glm::dot(c, c);

	if (bc*ac - cc * ab < 0.0f)
	{
		return false;
	}
	float bb = glm::dot(b, b);

	if (ab*bc - ac * bb < 0.0f)
	{
		return false;
	}
*/

	return true;


}

bool Triangle::pointIntersectPlane(glm::vec3 p, glm::vec3 dir, float & t)
{

	float denom = glm::dot(this->normal, dir);

	if (abs(denom) > 1e-6) {

		glm::vec3 diff = this->point1 - p;
		t = glm::dot(diff, this->normal) / denom;
		return (t >= 0.0f && t <=1.0f);
	}
	return false;

}

void Triangle::update(glm::mat4 transform)
{
	this->point1 = glm::vec4(this->point1, 0.0f) * transform;
	this->point2 = glm::vec4(this->point2, 0.0f) * transform;
	this->point3 = glm::vec4(this->point3, 0.0f) * transform;

}




