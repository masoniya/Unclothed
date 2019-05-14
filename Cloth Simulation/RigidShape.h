#pragma once

#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Triangle.h"

class RigidShape :public KeyboardControl
{
public:
	RigidShape(std::string path);
	
	 void draw(ShaderProgram program);
	 glm::mat4 getTransform();
	 void manageKeyboardInput(GLFWwindow *window);
	 bool intersectPoint(glm::vec3 point,glm::vec3 &dir);

	 std::vector<Triangle*> triangles;


	 //just for testing against a fake sphere
	 glm::vec3 center;
	 float radius;

private:
	Model * model;
	

	
	glm::vec3 pos;

	

};

