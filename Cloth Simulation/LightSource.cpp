#include <vector>

#include "LightSource.h"
#include "IndexedMesh.h"


LightSource::LightSource() :
	ambientColor{
		0.2f, 0.2f, 0.2f
	},
	diffuseColor{
		1.0f, 1.0f, 1.0f
	},
	specularColor{
		1.0f, 1.0f, 1.0f
	}
{
}

LightSource::LightSource(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
{
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
}

void LightSource::initDefaultMesh()
{
	float vertices[] = {
		-0.5f,  0.5f,  1.0f,
		 0.5f,  0.5f,  1.0f,
		 0.5f, -0.5f,  1.0f,
		-0.5f, -0.5f,  1.0f,
		-0.5f,  0.5f,  2.0f,
		 0.5f,  0.5f,  2.0f,
		 0.5f, -0.5f,  2.0f,
		-0.5f, -0.5f,  2.0f,
	};

	uint32_t indices[] = {
		0, 1, 2,
		2, 3, 0,
		1, 5, 6,
		6, 2, 1,
		3, 2, 6,
		6, 7, 3,
		4, 0, 3,
		3, 7, 4,
		4, 5, 1,
		1, 0, 4,
		4, 5, 6,
		6, 7, 4,
	};

	std::vector<Texture> textureVec; //empty
	std::vector<Vertex> vertexVec;
	std::vector<unsigned int> indexVec;

	for (int n = 0; n < sizeof(vertices) / sizeof(vertices[0]); n += 3) {
		vertexVec.push_back(Vertex(
			glm::vec3(vertices[n], vertices[n + 1], vertices[n + 2]),
			glm::vec3(0.0f),
			glm::vec2(0.0f)
		));
	}

	for (int i = 0; i < sizeof(indices) / sizeof(indices[0]); i++) {
		indexVec.push_back(indices[i]);
	}

	lightMesh = new IndexedMesh(vertexVec, indexVec, textureVec);
}

void LightSource::draw(ShaderProgram program)
{
	if (lightMesh != nullptr) {
		lightMesh->draw(program);
	}
	else {
		std::cout << "Light mesh uninitialized" << std::endl;
	}
}
