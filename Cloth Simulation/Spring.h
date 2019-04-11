#pragma once

#include "PointMass.h"
  

class Spring
{
public:
	Spring();
	Spring(float k, float d, PointMass* particle1, PointMass* particle2);
	
	float getRestLength();
	float getCurrentLength();
	
	void applyForce();
	
private:

	float springConst;
	float dampingConst;
	float restLength;
	PointMass *pointMass1;
	PointMass *pointMass2;

	void init(float k, float d,  PointMass* particle1, PointMass* particle2);
};
