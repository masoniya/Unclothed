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
	glm::vec3 getAmbientColor() { return ambientColor; }
	glm::vec3 getDiffuseColor() { return diffuseColor; }
	glm::vec3 getSpecularColor() { return specularColor; }
	glm::vec3 getDirection() { return direction; }
	glm::vec3 getAttenuation() { return attenuation; }

private:

	float vertices[48];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;

	glm::vec3 position;

	glm::vec3 direction; //for directional light

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

	glm::vec3 attenuation;
};
