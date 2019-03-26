#pragma once

#include<glm/glm.hpp>

class PointMass
{



public:

	PointMass();
	~PointMass();

	void init(float mass, glm::vec3 position, glm::vec3 velocity);

	void addForce(const glm::vec3 &force);
	void clearAccum();

	
	void update(float deltaTime);

	float getMass();

private:
	float mass;

	glm::vec3 position;
	glm::vec3 velocity;
	

	//for accumulating forces on the point Mass
	glm::vec3 forceAccum;






	


};

