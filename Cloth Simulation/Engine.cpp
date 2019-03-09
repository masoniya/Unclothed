#include <cmath>
#include <string>


#include "Engine.h"


Engine::Engine() :	vertices{ 
						//positions			 //color			//texture coords
						-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,	0.0f, 1.0f,				//top left
						 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	1.0f, 1.0f,				//top right
						 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	1.0f, 0.0f,				//bottom right
						-0.5f, -0.5f, 0.0f,  0.5f, 0.5f, 0.0f,	0.0f, 0.0f,				//bottom left

					},
					indices{
						0, 1, 2,
						2, 3, 0,
					},
					attribCount(0)
{
}


void Engine::init()
{
	initWindow();
	initShaderProgram();

	texture = new Texture(texturePath);

	createVertexObjects();
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window.getWindow())) {
		processInput(window.getWindow());

		renderFrame();

		glfwPollEvents();
	}
}

void Engine::cleanup()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	delete texture;

	window.close();
}

void Engine::initWindow()
{
	window.init(WIDTH, HEIGHT, "Engine");
	window.setClearColor(0.2f, 0.3f, 0.5f, 1.0f);
}

void Engine::initShaderProgram()
{
	program.compileShaders(vertexShaderPath, fragmentShaderPath);
}

void Engine::createVertexObjects()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	//bind the vao
	glBindVertexArray(vao);

	//bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind the ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Specify attributes of vertices in the buffer
	glVertexAttribPointer(attribCount++, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(attribCount++, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(attribCount++, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	enableAttributes();

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Don't unbind the ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//unbind the vao
	glBindVertexArray(0);
}

void Engine::enableAttributes()
{
	for (int i = 0; i < attribCount; i++) {
		glEnableVertexAttribArray(i);
	}
}

//TODO : Move input processing to a general input manager
void Engine::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Engine::renderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);

	program.useProgram();

	/*
	float time = (float)glfwGetTime();
	float modifier = sin(time);
	program.setUniformFloat("time", modifier);
	*/

	texture->useTexture();

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	window.swapBuffers();
}

void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
