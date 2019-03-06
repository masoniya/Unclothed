#pragma once
#include <cmath>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "ShaderProgram.h"
#include "Window.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const char* const vertexShaderPath = "shaders/shader.vert";
const char* const fragmentShaderPath = "shaders/shader.frag";

//This is also acceptable syntax for c strings as arrays are constant by nature
//const char vertexShaderPath[] = "shaders/shader.vert";
//const char fragmentShaderPath[] = "shaders/shader.frag";


class Engine
{
public:
	Engine();

	void start();

private:
	float vertices[18];
	uint32_t indices[3];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;

	ShaderProgram program;
	Window window;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void createVertexObjects();
	
	void processInput(GLFWwindow *window);
	void renderFrame();

};
