#include <string>
#include <iostream>
#include <fstream>

#include "ShaderProgram.h"


void ShaderProgram::compileShaders(const char *vertPath, const char *fragPath)
{
	uint32_t vertexShader;
	uint32_t fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertPath, vertexShader);
	compileShader(fragPath, fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::string errorMessage("Shader program linking failed");
		errorMessage += '\n';
		throw std::runtime_error(errorMessage);
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::useProgram()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::setUniformInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::setUniformFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}

void ShaderProgram::compileShader(const char *path, uint32_t shader)
{
	std::ifstream input(path);

	std::string source;
	std::string line;

	if (input.is_open()) {
		while (std::getline(input, line)) {
			source += line + '\n';
		}
	}
	else {
		std::string errorMessage("Shader file " + *path);
		errorMessage += " not found\n";
		throw std::runtime_error(errorMessage);
	}

	const char* tempContents = source.c_str();
	glShaderSource(shader, 1, &tempContents, nullptr);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::string errorMessage("Shader compilation failed " + *path);
		errorMessage += '\n';
		errorMessage += infoLog;
		throw std::runtime_error(errorMessage);
	}
}
