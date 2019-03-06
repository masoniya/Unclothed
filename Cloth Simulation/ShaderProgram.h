#pragma once
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>


class ShaderProgram
{
public:

	void compileShaders(const char* vertpath, const char* fragpath);
	void useProgram();
	void setUniformInt(const char* name, int value);
	void setUniformFloat(const char* name, float value);

private:

	uint32_t shaderProgram;

	void compileShader(const char* path, uint32_t id);

};
