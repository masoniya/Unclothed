#include <cmath>

#include "Engine.h"

float deltaTime = 0.0f;
float prevTime = 0.0f;

Engine::Engine() :	vertices{ 
						//Cube vertices
						//positions				//color				//texture coords
						-0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,				//top left
						 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,				//top right
						 0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,				//bottom right
						-0.5f, -0.5f,  0.5f,	0.5f, 0.5f, 0.0f,	0.0f, 0.0f,				//bottom left
						-0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,				//top left back
						 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,				//top right back
						 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,				//bottom right back
						-0.5f, -0.5f, -0.5f,	0.5f, 0.5f, 0.0f,	0.0f, 1.0f,				//bottom left back

					},
					indices{
						0, 1, 2,	//front face
						2, 3, 0,

						1, 5, 6,	//right face
						6, 2, 1,

						3, 2, 6,	//bottom face
						6, 7, 3,

						4, 0, 3,	//left face
						3, 7, 4,

						4, 5, 1,	//top face
						1, 0, 4,

						4, 5, 6,	//back face
						6, 7, 4,
					},
					attribCount(0)
{
}


void Engine::init()
{
	window = new Window;

	initWindow();
	initShaderProgram();

	inputManager = new InputManager(window->getWindow());
	inputManager->registerKeyboardInput(window);

	wallTexture = new Texture(wallPath);
	faceTexture = new Texture(facePath);

	mainCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	inputManager->registerKeyboardInput(mainCamera);
	inputManager->registerMouseInput(mainCamera);


	createVertexObjects();

	glEnable(GL_DEPTH_TEST);
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window->getWindow())) {
		float currentTime = (float)glfwGetTime();
		deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		inputManager->handleKeyboardInput();

		renderFrame();

		glfwPollEvents();
	}
}

void Engine::cleanup()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	delete wallTexture;
	delete faceTexture;

	window->close();
}

void Engine::initWindow()
{
	window->init(WIDTH, HEIGHT, "Engine");
	window->setClearColor(0.2f, 0.3f, 0.5f, 1.0f);
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

void Engine::renderFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//transformation code (move somewhere else)
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(30.0f), glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f)));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	/*
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	*/

	glm::mat4 view = mainCamera->view();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float) WIDTH / HEIGHT, 0.1f, 100.0f);

	program.useProgram();

	program.setUniformInt("textureSampler", 0);
	program.setUniformInt("textureSampler2", 1);
	program.setUniformMat4("model", glm::value_ptr(model));
	program.setUniformMat4("view", glm::value_ptr(view));
	program.setUniformMat4("projection", glm::value_ptr(projection));


	glActiveTexture(GL_TEXTURE0);
	wallTexture->useTexture();

	glActiveTexture(GL_TEXTURE1);
	faceTexture->useTexture();

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	window->swapBuffers();
}

void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
