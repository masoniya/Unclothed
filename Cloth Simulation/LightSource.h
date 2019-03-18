#pragma once
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource();

	void init();
	void use();
	void unuse();

	glm::vec3 getPosition() { return position; }
	glm::vec3 getLightColor() { return lightColor; }

private:

	float vertices[48];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;

	glm::vec3 position;
	glm::vec3 lightColor;
};
