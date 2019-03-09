#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int Texture::minFilter = GL_LINEAR_MIPMAP_LINEAR;
int Texture::magFilter = GL_LINEAR;

//in this constructor the filters used are the global filters
Texture::Texture(std::string texturePath)
{
	construct(texturePath, minFilter, magFilter);
}

//in this constructor the filters are passed as parameters
Texture::Texture(std::string texturePath, int minFilter, int magFilter)
{
	construct(texturePath, minFilter, magFilter);
}



void Texture::useTexture()
{
	//Automatically assigns the texture to the fragment shader's sampler
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::construct(std::string texturePath, int minFilter, int magFilter)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	//wrapping options (currently unchangeable)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	//filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	int width, height, numChannels;
	unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &numChannels, 0);

	if (data != nullptr) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		throw std::runtime_error("Failed to load texture");
	}
	stbi_image_free(data);


}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::setMinFilter(int filter)
{
	minFilter = filter;
}

void Texture::setMagFilter(int filter)
{
	magFilter = filter;
}