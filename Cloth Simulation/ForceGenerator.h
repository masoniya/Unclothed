#pragma once

#include "PointMass.h"

class ForceGenerator
{


public:
	ForceGenerator();
	~ForceGenerator();


	virtual void applyForce(PointMass* pointmass)=0;
};

