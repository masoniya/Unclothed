#pragma once

#include "ForceGenerator.h"
#include "PointMass.h"

#include "glm/glm.hpp"

class Gravity : public ForceGenerator
{
public:
	Gravity();
	~Gravity();

	virtual void applyForce(PointMass* pointmass);


private:
	glm::vec3 gravity;


};

