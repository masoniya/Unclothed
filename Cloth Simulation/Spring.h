#pragma once

#include "PointMass.h"
#include <vector>
  



class Spring
{
public:

	Spring();
	Spring(float, float, PointMass *, PointMass *);
	

	float getRestLength();
	float getCurrentLength();
	

	

	void applyForce();
	
	

private:

	float springConst;
	float dampingConst;
	float restLength;
	PointMass *pointMass1;
	PointMass *pointMass2;


	void init(float, float,  PointMass*, PointMass*);


};

