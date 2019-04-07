#pragma once

#include "PointMass.h"
#include <vector>

class Integrator
{
public:

	virtual void solve(float deltaTime) = 0;
	

protected:

	std::vector<PointMass*> points;


};

