#pragma once

#include<vector>
#include "PointMass.h"
#include "ForceGenerator.h"
#include "Integrator.h"
#include "Face.h"

class DeformableBody
{
	

public:
	virtual void update(float deltaTime) = 0;
	


protected:

	std::vector<PointMass*> points;
	std::vector<Face*> faces;
	std::vector<ForceGenerator*> externalForces;

	Integrator* solver;



};

