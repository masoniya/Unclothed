#pragma once

#include "Integrator.h"
#include <vector>
class SemiImpEuler : public Integrator
{
public:
	SemiImpEuler(std::vector<PointMass*> points);

	void solve(float fixedDeltaTime);






};

