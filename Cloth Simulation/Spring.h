#pragma once

#include "PointMass.h"

  

class Spring
{
public:
	Spring();
	Spring(float, float, PointMass *, PointMass *,float);
	
	float getRestLength();
	float getCurrentLength();
	
	void setMasterPoint(PointMass* master);

	void applyForce();
	void adjust();
	
private:

	float springConst;
	float dampingConst;
	float restLength;
	PointMass** pointMasses;

	int masterPoint;
	float maxDeformRate;

	void init(float, float,  PointMass*, PointMass*,float);
};
