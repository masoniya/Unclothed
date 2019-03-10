#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Window.h"
#include "Texture.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const char* const vertexShaderPath = "shaders/shader.vert";
const char* const fragmentShaderPath = "shaders/shader.frag";

const char* const wallPath = "resources/wall.jpg";
const char* const facePath = "resources/pepe.png";

//This is also acceptable syntax for c strings as arrays are constant by nature
//const char vertexShaderPath[] = "shaders/shader.vert";
//const char fragmentShaderPath[] = "shaders/shader.frag";


class Engine
{
public:
	Engine();

	void start();

private:
	float vertices[64];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;
	int attribCount;

	ShaderProgram program;
	Window window;
	Texture *wallTexture;
	Texture *faceTexture;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void createVertexObjects();
	void enableAttributes();
	
	void processInput(GLFWwindow *window);
	void renderFrame();

};
