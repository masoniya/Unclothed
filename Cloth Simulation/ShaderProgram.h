#pragma once

#include <glad/glad.h>



class ShaderProgram
{
public:

	void compileShaders(const char* vertPath, const char* fragPath);
	void useProgram();
	void setUniformInt(const char* name, int value);
	void setUniformFloat(const char* name, float value);
	void setUniformMat4(const char* name, const float *value);

private:

	uint32_t shaderProgram;

	void compileShader(const char* path, uint32_t shader);

};
