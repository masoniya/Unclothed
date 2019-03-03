#include "Engine.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


Engine::Engine() : vertices{ -0.5f, -0.5f, 0.0f,
							0.5f, -0.5f, 0.0f,
							0.0f, 0.5f, 0.0f }
{
}



void Engine::init()
{
	initWindow();
	initGlad();
	setFramebufferSize(WIDTH, HEIGHT);
	initShaderProgram();
	configure();
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Engine::cleanup()
{
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

void Engine::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Engine::createVertexBuffer()
{
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
}

void Engine::initShaderProgram()
{
	program.init();
}

void Engine::configure()
{
	createVertexBuffer();
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Engine::render()
{
	glClearColor(0.4f, 0.3f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	program.start();
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}




void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
