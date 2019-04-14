#pragma once

#include <vector>
#include <set>

#include "DeformableBody.h"
#include "Spring.h"
#include "PointMass.h"
#include "Face.h"
#include "KeyboardControl.h"
#include "SpringPointMass.h"



const float k_const_structure = 300.0f;
const float k_const_shear = 300.0f;
const float k_const_bending = 300.0f;

const float damp = 0.1f;

class Cloth : public DeformableBody, public KeyboardControl
{
public:
	Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height,float mass);
	
	void init(glm::vec3 top_left,int num_cols , int num_rows, float width, float height, float mass);
	void update(float deltaTime);

	float* getVertexData();

	int width, height;

	void manageKeyboardInput(GLFWwindow *window) override;

private:

	std::vector<Spring*> allSprings;
	SpringPointMass **allPoints;
	std::vector<Spring*> adjustableSprings;
	set<SpringPointMass*> fixedPoints;

	float* vertexData;
	float mass;

	bool buttonDown;
	bool useVertexNormals;

	void buildOrderedSprings();

};
