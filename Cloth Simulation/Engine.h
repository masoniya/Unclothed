#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Vertex.h"
#include "ShaderProgram.h"
#include "errors.h"


const int WIDTH = 800;
const int HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

class Engine
{
private:
	GLFWwindow *window;
	float vertices[9];
	uint32_t vbo;
	uint32_t vao;

	ShaderProgram program;

	void init();
	void mainLoop();
	void cleanup();
	

	void initWindow();
	void initGlad();
	void setFramebufferSize(int width, int height);

	void processInput(GLFWwindow *window);

	void createVertexBuffer();

	void initShaderProgram();

	void configure();
	
	void render();

public:
	Engine();

	void start();
};

