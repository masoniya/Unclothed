#pragma once

#include "Integrator.h"

class SemiImpEuler : public Integrator
{
public:
	SemiImpEuler();

	void solve(float deltaTime);

private:




};

