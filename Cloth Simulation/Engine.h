#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Window.h"
#include "Texture.h"
#include "Camera.h"
#include "InputManager.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const char* const vertexShaderPath = "shaders/shader.vert";
const char* const fragmentShaderPath = "shaders/shader.frag";

//This is also acceptable syntax for c strings as arrays are constant by nature
//const char vertexShaderPath[] = "shaders/shader.vert";
//const char fragmentShaderPath[] = "shaders/shader.frag";

const std::string wallPath = "resources/wall.jpg";
const std::string facePath = "resources/pepe.png";


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
	Window *window;
	Texture *wallTexture;
	Texture *faceTexture;
	Camera *mainCamera;
	InputManager *inputManager;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void createVertexObjects();
	void enableAttributes();
	
	void renderFrame();

};
