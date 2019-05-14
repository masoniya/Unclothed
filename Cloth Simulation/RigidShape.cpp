#include "RigidShape.h"


extern float deltaTime;

RigidShape::RigidShape(std::string path)
{
	model = new Model(path);

	std::vector<IndexedMesh> meshes = model->getMesh();
	
	for (IndexedMesh mesh : meshes) {
		
		for (int i = 0; i < mesh.indices.size(); i += 3)
		{
			int index1 = mesh.indices[i];
			int index2 = mesh.indices[i + 1];
			int index3 = mesh.indices[i + 2];


			Triangle *triangle = new Triangle(mesh.vertices[index1].position, mesh.vertices[index2].position, mesh.vertices[index3].position);
			//Triangle *triangle = new Triangle(mesh.vertices[i].position, mesh.vertices[i+1].position, mesh.vertices[i+2].position);

			this->triangles.push_back(triangle);


		}

	}

	pos = glm::vec3(0.0f, 0.0f, -5.0f);

	center = glm::vec3(0.0f, -0.2f, 0.0f);
	radius = 0.3f;

}

void RigidShape::draw(ShaderProgram program)
{
	model->draw(program);

}

glm::mat4 RigidShape::getTransform()
{

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,pos);
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	return model;
}

void RigidShape::manageKeyboardInput(GLFWwindow * window)
{
	float speed = 2.0f*deltaTime;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		//pos += speed * glm::vec3(0.0f, 0.0f, 1.0f);
		center += speed * glm::vec3(0.0f, 0.0f, 1.0f);

		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		//pos -= speed * glm::vec3(0.0f, 0.0f, 1.0f);
		center -= speed * glm::vec3(0.0f, 0.0f, 1.0f);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		//pos -= speed * glm::vec3(1.0f, 0.0f, 0.0f);
		center -= speed * glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		//pos += speed * glm::vec3(1.0f, 0.0f, 0.0f);
		center += speed * glm::vec3(1.0f, 0.0f, 0.0f);



	for (Triangle* tri : triangles) {

		tri->update(this->getTransform());
	}

}

bool RigidShape::intersectPoint(glm::vec3 point,glm::vec3 &dir)
{
	glm::vec3 diff = point - this->center;
	dir = glm::normalize(diff);
	if (glm::length(diff) < this->radius) {
		
		return true;
	}
	return false;
	
}



