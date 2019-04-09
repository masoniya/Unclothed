#pragma once

#include <vector>

#include "Integrator.h"


class SemiImpEuler : public Integrator
{
public:
	SemiImpEuler(std::vector<PointMass*> points);

	void solve(float fixedDeltaTime);
};
