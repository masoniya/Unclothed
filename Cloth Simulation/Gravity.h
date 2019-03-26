#pragma once

#include "ForceGenerator.h"
#include "PointMass.h"

#include "glm/glm.hpp"



class Gravity : public ForceGenerator
{
public:
	Gravity();
	Gravity(glm::vec3 gravity);
	

	virtual void applyForce();


private:
	glm::vec3 gravity;
	std::vector<PointMass*> points;

	
	

};

