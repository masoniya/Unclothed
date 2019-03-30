#include <cmath>
#include <sstream>
#include <vector>

#include "Engine.h"


Engine::Engine() :	
	vertices{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,	1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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

	camera = new Camera(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	inputManager->registerKeyboardInput(camera);
	inputManager->registerMouseInput(camera);
	inputManager->registerScrollInput(camera);

	material = new Material(diffPath, specPath, 32.0f);

	//createVertexObjects();
	initMesh();

	initLights();
	
	glEnable(GL_DEPTH_TEST);
}

void Engine::mainLoop()
{
	while (!glfwWindowShouldClose(window->getWindow())) {
		fpsCounter.update();

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

	delete material;

	window->close();
}

void Engine::initWindow()
{
	window->init(WIDTH, HEIGHT, "Engine");
	window->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Engine::initShaderProgram()
{
	program.compileShaders(vertexShaderPath, fragmentShaderPath);
	lampProgram.compileShaders(lampVertShaderPath, lampFragShaderPath);
}

void Engine::initLights()
{
	Attenuation attenuation;
	attenuation.constant = 1.0f;
	attenuation.linear = 0.045f;
	attenuation.quadratic = 0.0075f;
	
	glm::vec3 yellow = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 white = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);

	sunlight = new DirectionalLight(0.05f * yellow, 0.7f * yellow, 0.5f * white, glm::vec3(-0.2f, -1.0f, 0.2f));

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	glm::vec3 pointLightColors[] = {
		glm::vec3(0.1f,  0.22f, 0.9f),
		glm::vec3(0.72f, 0.4f, 0.83f),
		glm::vec3(0.4f,  0.94f, 0.52f),
		glm::vec3(0.7f,  0.2f,  0.1f)
	};

	for (int i = 0; i < 4; i++) {
		lamps[i] = new PointLight(0.1f * pointLightColors[i], 1.5f * pointLightColors[i], white,
			pointLightPositions[i], attenuation);
		lamps[i]->initDefaultMesh();
	}

	flashlight = new SpotLight(0.1f * white, white, white, camera->getCameraPosition(), camera->getCameraFront(),
		cos(glm::radians(12.5f)), cos(glm::radians(17.5f)), attenuation);

	inputManager->registerKeyboardInput(flashlight);
}

void Engine::initMesh()
{
	std::vector<Texture> textureVec;
	std::vector<Vertex> vertexVec;

	textureVec.push_back(Texture(diffPath));
	textureVec.back().type = TextureType::texture_diffuse;

	textureVec.push_back(Texture(specPath));
	textureVec.back().type = TextureType::texture_specular;

	//the rule of three (also don't do opengl stuff in the destructor)
	//textureVec.push_back(*material->diffuseMap);
	//textureVec.push_back(*material->specularMap);

	for (int n = 0; n < sizeof(vertices) / sizeof(vertices[0]); n += 8) {
		vertexVec.push_back(Vertex(
			glm::vec3(vertices[n], vertices[n + 1], vertices[n + 2]),
			glm::vec3(vertices[n + 3], vertices[n + 4], vertices[n + 5]),
			glm::vec2(vertices[n + 6], vertices[n + 7])
		));
	}

	cubeMesh = new Mesh(vertexVec, textureVec);
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

	glm::mat4 view = camera->view();
	glm::mat4 projection = camera->project();
	flashlight->position = camera->getCameraPosition();
	flashlight->direction = camera->getCameraFront();

	program.useProgram();

	program.setUniformMat4("view", view);
	program.setUniformMat4("projection", projection);

	//material (figure out where to put the shininess)
	program.setUniformFloat("material.shininess", material->shininess);

	//directional light
	program.setUniformDirLight("dirLights[0]", *sunlight);

	//point light
	for (int i = 0; i < 4; i++) {
		std::ostringstream out;
		out << "pointLights[" << i << "]";
		program.setUniformPointLight(out.str(), *lamps[i]);
	}
	
	//spotlight
	program.setUniformSpotLight("spotLights[0]", *flashlight);

	//view position (useful for specular lighting)
	program.setUniformVec3("viewPosition", &(camera->getCameraPosition())[0]);

	//draw 10 boxes
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		program.setUniformMat4("model", model);

		cubeMesh->draw(program);
	}

	lampProgram.useProgram();

	//draw the lamp cubes
	for (int i = 0; i < 4; i++) {
		glm::mat4 lampModel = glm::mat4(1.0f);
		lampModel = glm::translate(lampModel, lamps[i]->position);
		lampModel = glm::scale(lampModel, glm::vec3(0.2f));

		lampProgram.setUniformMat4("model", &lampModel[0][0]);
		lampProgram.setUniformMat4("view", &view[0][0]);
		lampProgram.setUniformMat4("projection", &projection[0][0]);

		lampProgram.setUniformVec3("lightColor", lamps[i]->diffuseColor);

		lamps[i]->draw(program);
	}

	window->swapBuffers();
}

void Engine::start()
{
	init();
	mainLoop();
	cleanup();
}
