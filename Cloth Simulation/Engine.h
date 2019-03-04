#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <string>

#include "Vertex.h"
#include "ShaderProgram.h"
#include "errors.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const std::string vertexShaderPath = "shaders/shader.vert";
const std::string fragmentShaderPath = "shaders/shader.frag";

void framebufferSizeCallback(GLFWwindow *window, int width, int height);

class Engine
{

public:
	Engine();

	void start();

private:
	GLFWwindow *window;
	float vertices[12];
	uint32_t indices[6];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;

	ShaderProgram program;

	void init();
	void mainLoop();
	void cleanup();
	

	void initWindow();
	void initGlad();
	void setFramebufferSize(int width, int height);
	void initShaderProgram();
	void createVertexObjects();

	

	
	void processInput(GLFWwindow *window);
	void renderFrame();


};

