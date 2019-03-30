#pragma once

#include <string>

#include <glad/glad.h>


enum class TextureType { texture_diffuse, texture_specular };

class Texture
{
public:
	Texture(std::string texturePath);
	Texture(std::string texturePath, int minFilter, int magFilter);

	~Texture();

	void useTexture();

	static void setMinFilter(int filter);
	static void setMagFilter(int filter);

	uint32_t texture;
	TextureType type;

private:
	void construct(std::string texturePath, int minFilter, int magFilter);

	static int minFilter;
	static int magFilter;

};
