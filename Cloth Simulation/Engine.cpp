#include "Engine.h"



void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


Engine::Engine() : vertices{ 
						 0.5f,  0.5f, 0.0f,
						 0.5f, -0.5f, 0.0f,
						-0.5f, -0.5f, 0.0f,
						-0.5f,  0.5f, 0.0f 
					},
					indices{
						0, 1, 3,
						1, 2, 3
					}
{
}



void Engine::init()
{
	initWindow();
	initGlad();
	setFramebufferSize(WIDTH, HEIGHT);
	initShaderProgram();
	createVertexObjects();
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		renderFrame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Engine::cleanup()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	glfwTerminate();
}

void Engine::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Engine", nullptr, nullptr);

	if (window == nullptr) {
		logError("Failed to create window.");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
}

void Engine::initGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		logError("Failed to initialize GLAD.");
		glfwTerminate();
	}
}

void Engine::setFramebufferSize(int width, int height)
{
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void Engine::initShaderProgram()
{
	program.compileShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//unbind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Don't unbind the ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//unbind the vao
	glBindVertexArray(0);
	
}

void Engine::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Engine::renderFrame()
{
	glClearColor(0.4f, 0.3f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	program.useProgram();
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}




void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
