#pragma once

#include <string>

#include <glad/glad.h>


class Texture
{
public:
	Texture(std::string texturePath);
	Texture(std::string texturePath, int minFilter, int magFilter);

	~Texture();

	void useTexture();

	static void setMinFilter(int filter);
	static void setMagFilter(int filter);

private:
	uint32_t texture;

	void construct(std::string texturePath, int minFilter, int magFilter);

	static int minFilter;
	static int magFilter;

	
};
