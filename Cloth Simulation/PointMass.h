#pragma once

#include<glm/glm.hpp>
#include <iostream>

class PointMass
{



public:

	PointMass();
	PointMass(float, glm::vec3,bool);
	

	
	void addForce(const glm::vec3 &force);
	void clearAccum();
	
	
	
	float getMass();
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();


	void setPosition(glm::vec3 pos);
	void setVelocity(glm::vec3 vel);
	void setMass(float mass);
	void setImmovable();

	void printPos();

private:
	float mass;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 forceAccum;

	bool immovable;

	void init(float mass, glm::vec3 position, glm::vec3 velocity,bool immovable);





	


};

