#pragma once

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>


struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

class LightSource
{
public:
	LightSource();
	LightSource(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);

	void init();
	void use();
	void unuse();

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;

private:
	float vertices[24];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;

};
