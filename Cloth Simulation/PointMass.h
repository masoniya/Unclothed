#pragma once

#include <iostream>
#include <vector>

#include <glm/glm.hpp>


class PointMass
{
public:
	PointMass();
	PointMass(float, glm::vec3, bool);
	
	void addForce(const glm::vec3 &force);
	void clearAccum();
	
	float getMass();
	glm::vec3 getPosition();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();
	glm::vec3 getNormal();

	void setPosition(glm::vec3 pos);
	void setVelocity(glm::vec3 vel);
	void setMass(float mass);
	void setImmovable();
	void addNormal(glm::vec3 normal);
	void calculatePointNormal();

	void printPos();

private:
	float mass;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 forceAccum;
	glm::vec3 pointNormal;
	std::vector<glm::vec3> normalAccum;

	bool immovable;

	void init(float mass, glm::vec3 position, glm::vec3 velocity, bool immovable);

};
