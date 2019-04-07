#pragma once

#include <vector>
#include "DeformableBody.h"
#include "Spring.h"
#include "PointMass.h"
#include "Face.h"

const float k_const_structure = 600.0f;
const float k_const_shear = 600.0f;
const float k_const_bending = 600.0f;

const float damp = 0.5f;



class Cloth :public DeformableBody
{
public:
	Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height,float mass);
	

	void init(glm::vec3 top_left,int num_cols , int num_rows, float width, float height, float mass);
	void  update(float deltaTime);

	float* getVertexData();

	int width, height;

private:

	std::vector<Spring*> allSprings;
	PointMass **allPoints;
	float* vertexData;

	float mass;

	//float * vertexData;


};

