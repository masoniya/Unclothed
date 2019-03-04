#include <iostream>
#include <fstream>

#include "ShaderProgram.h"
#include "errors.h"


void ShaderProgram::compileShaders(const char *vertpath, const char *fragpath)
{
	uint32_t vertshaderid;
	uint32_t fragshaderid;

	vertshaderid = glCreateShader(GL_VERTEX_SHADER);
	fragshaderid = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertpath, vertshaderid);
	compileShader(fragpath, fragshaderid);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertshaderid);
	glAttachShader(shaderProgram, fragshaderid);
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

	glDeleteShader(vertshaderid);
	glDeleteShader(fragshaderid);
}

void ShaderProgram::useProgram()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::compileShader(const char *path, uint32_t id)
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
	glShaderSource(id, 1, &tempContents, nullptr);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::string errorMessage("Shader compilation failed " + *path);
		errorMessage += '\n';
		errorMessage += infoLog;
		throw std::runtime_error(errorMessage);
	}
}
