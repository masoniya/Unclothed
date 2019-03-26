#pragma once

#include <vector>
#include "DeformableBody.h"
#include "Spring.h"
#include "PointMass.h"
#include "Face.h"






class Cloth : DeformableBody
{
public:
	Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height);
	~Cloth();

	void init(glm::vec3 ,int ,int ,float ,float);
	 void  update(float deltaTime);

private:

	std::vector<Spring*> allSprings;
	PointMass **allPoints;

};

