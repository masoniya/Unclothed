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

const std::string diffPath = "resources/box_diffuse.png";
const std::string specPath = "resources/box_specular.png";

struct Material {
	Texture *diffuseMap;
	Texture *specularMap;
	float shininess;

	Material(std::string diffMapPath, std::string specMapPath, float shininess) {
		this->diffuseMap = new Texture(diffMapPath);
		this->specularMap = new Texture(specMapPath);
		this->shininess = shininess;
	}

	~Material() {
		delete diffuseMap;
		delete specularMap;
	}
};

class Engine
{
public:
	Engine();

	void start();

private:
	float vertices[288];
	uint32_t indices[36];
	uint32_t vbo;
	uint32_t vao;
	uint32_t ebo;
	int attribCount;

	ShaderProgram program;
	ShaderProgram lightProgram;
	Window *window;
	Camera *camera;
	InputManager *inputManager;
	LightSource *lightSource;
	Material *material;

	void init();
	void mainLoop();
	void cleanup();
	
	void initWindow();
	void initShaderProgram();
	void createVertexObjects();
	void enableAttributes();
	
	void renderFrame();

};
