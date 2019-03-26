#include "LightSource.h"


LightSource::LightSource() :
	vertices{
		-0.5f,  0.5f,  1.0f,
		 0.5f,  0.5f,  1.0f,
		 0.5f, -0.5f,  1.0f,
		-0.5f, -0.5f,  1.0f,
		-0.5f,  0.5f,  2.0f,
		 0.5f,  0.5f,  2.0f,
		 0.5f, -0.5f,  2.0f,
		-0.5f, -0.5f,  2.0f,
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

LightSource::LightSource(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor) :
	vertices{
		-0.5f,  0.5f,  1.0f,
		 0.5f,  0.5f,  1.0f,
		 0.5f, -0.5f,  1.0f,
		-0.5f, -0.5f,  1.0f,
		-0.5f,  0.5f,  2.0f,
		 0.5f,  0.5f,  2.0f,
		 0.5f, -0.5f,  2.0f,
		-0.5f, -0.5f,  2.0f,
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
	}
{
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
}

void LightSource::init()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void LightSource::use()
{
	glBindVertexArray(vao);
}

void LightSource::unuse()
{
	glBindVertexArray(0);
}
