#pragma once

#include<vector>

#include "PointMass.h"
#include "ForceGenerator.h"
#include "Integrator.h"
#include "Face.h"
#include "Gravity.h"
#include "Drag.h"


class DeformableBody :public Gravity,public Drag
{
public:
	virtual void update(float deltaTime) = 0;
	
	void applyGravity(glm::vec3 gravity);
	void applyDrag(float damp);

protected:
	std::vector<PointMass*> points;
	std::vector<Face*> faces;
	
	Integrator* solver;

};
