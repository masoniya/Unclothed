#pragma once

#include "PointMass.h"

class Face
{
public:
	Face(PointMass* point1, PointMass* point2, PointMass * point3);
	
	float getArea();


private:
	PointMass *point1, *point2, *point3;
	glm::vec3 normal;

	void init(PointMass* ,PointMass* , PointMass*);
	void calcNormal();

};

