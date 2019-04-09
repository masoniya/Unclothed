#pragma once

#include "Drag.h"
#include "ForceGenerator.h"


class DragForce : public ForceGenerator
{
public:
	void applyForce();
	void addPhysicalObject(Drag* body);

	DragForce();
	DragForce(float damp);

private:

	float damp;
	std::vector<Drag*> physicalObjects;

};
