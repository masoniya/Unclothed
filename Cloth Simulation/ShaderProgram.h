#pragma once
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

class ShaderProgram
{
public:

	void init();
	void start();
	

private:
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	uint32_t vertexShader;
	uint32_t fragmentShader;
	uint32_t shaderProgram;

	void createShaders();
	void readShaders();
	void compileShaders();
	void createProgram();
};

