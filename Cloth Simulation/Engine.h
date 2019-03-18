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
#include "LightSource.h"


const int WIDTH = 800;
const int HEIGHT = 600;

const char* const vertexShaderPath = "shaders/shader.vert";
const char* const fragmentShaderPath = "shaders/shader.frag";

const char lampVertShaderPath[] = "shaders/LampShader.vert";
const char lampFragShaderPath[] = "shaders/LampShader.frag";

const std::string wallPath = "resources/wall.jpg";
const std::string facePath = "resources/pepe.png";

const glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

class Engine
{
public:
	Engine();

	void start();

private:
	float vertices[216];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;
	int attribCount;

	ShaderProgram program;
	Window *window;
	Texture *wallTexture;
	Texture *faceTexture;
	Camera *camera;
	InputManager *inputManager;
	LightSource *lightSource;
	ShaderProgram lightProgram;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void createVertexObjects();
	void enableAttributes();
	
	void renderFrame();

};
