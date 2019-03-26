#pragma once

#include "PointMass.h"
#include <vector>
  
const float structural_const = 1;
const float bending_const = 1;
const float shearing_const = 1;

const float structural_damp = 1;
const float bending_damp = 1;
const float shearing_damp = 1;


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

