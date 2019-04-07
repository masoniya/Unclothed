#pragma once

#include <vector>
#include "DeformableBody.h"
#include "Render.h"

class PhysicsEngine
{
public:
	PhysicsEngine(Render* renderer);
	void updatePhyics(float deltaTime);


private:	
	std::vector<DeformableBody*> physicalObjects;
	std::vector<ForceGenerator*> externalForces;

	Render * renderer;

	float timeAccumulator;
	float timeStep;

	void updateRenderer();

	int width;
	int height;


};

