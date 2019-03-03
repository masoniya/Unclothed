#include <iostream>
#include <fstream>

#include "ShaderProgram.h"
#include "errors.h"

//TODO : Clean up this mess of a class


void ShaderProgram::init()
{
	createShaders();
	readShaders();
	compileShaders();
	createProgram();
}

void ShaderProgram::start()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::readShaders()
{
	std::ifstream vertexIn;
	std::ifstream fragmentIn;
	std::string vertexSource;
	std::string fragmentSource;
	std::string line;

	vertexIn.open("shaders/shader.vert");
	if (vertexIn.is_open()) {
		while (std::getline(vertexIn, line)) {
			vertexSource += line + '\n';
		}
	}
	else {
		logError("Vertex shader not found");
	}
	vertexShaderSource = vertexSource.c_str();
	vertexIn.close();

	
	fragmentIn.open("shaders/shader.frag");
	if (fragmentIn.is_open()) {
		while (std::getline(fragmentIn, line)) {
			fragmentSource += line + '\n';
		}
	}
	else {
		logError("Fragment shader not found");
	}
	fragmentShaderSource = fragmentSource.c_str();
	fragmentIn.close();
	
}

void ShaderProgram::compileShaders()
{
	const char* tempContents = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &tempContents, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* tempContents2 = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &tempContents2, nullptr);
	glCompileShader(fragmentShader);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::createShaders()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

void ShaderProgram::createProgram()
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
