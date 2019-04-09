#include <iostream>

#include "Cloth.h"
#include "SemiImpEuler.h"


Cloth::Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height,float mass)
{
	init(top_left, num_cols, num_rows, width, height,mass);
}


void Cloth::init(glm::vec3 top_left,int num_cols , int num_rows, float width,float height,float mass)
{
	//initialize the particles array
	this->width = num_cols;
	this->height = num_rows;
	this->mass = mass;

	int size = (num_cols - 1) * (num_rows - 1) * 8 * 6;
	this->vertexData = new float[size];

	allPoints = new PointMass*[num_rows];

	for (int i = 0; i < num_rows; i++) {
		allPoints[i] = new PointMass[num_cols];
	}

	//initialize positions for particles
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {

			float newX = top_left.x + ((float)j / num_cols) * width;
			float newY = top_left.y ;
			float newZ = top_left.z + ((float)i / num_rows) * height;

			allPoints[i][j].setPosition(glm::vec3(newX , newY, newZ));
			allPoints[i][j].setMass(mass / width * height);

			if  (i == 0 && j == 0) {
				allPoints[i][j].setImmovable();
			}
			if (i == 0 && j == num_cols - 1) {
				allPoints[i][j].setImmovable();
			}

			/*if (i == num_rows-1 && j == 0) {
				allPoints[i][j].setImmovable();
			}
			if (i == num_rows-1 && j == num_cols - 1) {
				allPoints[i][j].setImmovable();
			}*/

			/*if (i == 0) {
				allPoints[i][j].setImmovable();

			}*/

			points.push_back(&allPoints[i][j]);

		}
	}
	
	// add springs
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < num_cols; j++) {

			// structural springs
			if (j + 1 < num_cols) {
				allSprings.push_back(new Spring(k_const_structure, damp, &allPoints[i][j], &allPoints[i][j + 1]));
			}
			if (i + 1 < num_rows) {
				allSprings.push_back(new Spring(k_const_structure, damp, &allPoints[i][j], &allPoints[i + 1][j]));
			}

			//shear springs
			if (i + 1 < num_rows ) {
				if (j + 1 < num_cols) {
					allSprings.push_back(new Spring(k_const_shear, damp, &allPoints[i][j], &allPoints[i + 1][j + 1]));
				}

				if (j - 1 >= 0) {
					allSprings.push_back(new Spring(k_const_shear, damp, &allPoints[i][j], &allPoints[i + 1][j - 1]));
				}
			}

			//bending springs
			if (j + 2 < num_cols) {
				allSprings.push_back(new Spring(k_const_bending, damp, &allPoints[i][j], &allPoints[i][j + 2]));
			}
			if (i + 2 < num_rows) {
				allSprings.push_back(new Spring(k_const_bending, damp, &allPoints[i][j], &allPoints[i + 2][j]));
			}

		}
	}
	
	// add the faces
	for (int i = 0; i < num_rows - 1; i++) {
		for (int j = 0; j < num_cols - 1; j++) {

			Face* face1 = new Face(&allPoints[i][j], &allPoints[i + 1][j], &allPoints[i + 1][j + 1]);
			Face* face2 = new Face(&allPoints[i][j], &allPoints[i + 1][j + 1], &allPoints[i][j + 1]);

			faces.push_back(face1);
			faces.push_back(face2);

		}
	}

	solver = new SemiImpEuler(points);

	/*for (int i = 0; i < num_rows ; i++) {

		for (int j = 0; j < num_cols ; j++) {

			allPoints[i][j].printPos();

		}
	}
	std::cout << "\n..............................................\n";*/

	buttonDown = false;
	useVertexNormals = true;
}

void Cloth::update(float deltaTime)
{
	//apply internal forces
	for (Spring* spring : allSprings) {
		spring->applyForce();

	}
	solver->solve(deltaTime);
}

float * Cloth::getVertexData()
{
	int offset = 0;

	float texCoordXStep = 1.0f / (width - 1);
	float texCoordYStep = 1.0f / (height - 1);

	if (useVertexNormals) {
		for (Face *face : faces) {
			face->calcNormal();
			face->updatePointNormals();
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				allPoints[i][j].calculatePointNormal();
			}
		}
	}

	for (int i = 0; i < height - 1; i++) {

		for (int j = 0; j < width - 1; j++) {

			if (useVertexNormals) {
				PointMass topLeft = allPoints[i][j];
				PointMass bottomLeft = allPoints[i + 1][j];
				PointMass bottomRight = allPoints[i + 1][j + 1];
				PointMass topRight = allPoints[i][j + 1];

				//top left
				vertexData[offset++] = topLeft.getPosition().x;
				vertexData[offset++] = topLeft.getPosition().y;
				vertexData[offset++] = topLeft.getPosition().z;

				vertexData[offset++] = topLeft.getNormal().x;
				vertexData[offset++] = topLeft.getNormal().y;
				vertexData[offset++] = topLeft.getNormal().z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;

				//bottom left
				vertexData[offset++] = bottomLeft.getPosition().x;
				vertexData[offset++] = bottomLeft.getPosition().y;
				vertexData[offset++] = bottomLeft.getPosition().z;

				vertexData[offset++] = bottomLeft.getNormal().x;
				vertexData[offset++] = bottomLeft.getNormal().y;
				vertexData[offset++] = bottomLeft.getNormal().z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 0.0f;

				//bottom right
				vertexData[offset++] = bottomRight.getPosition().x;
				vertexData[offset++] = bottomRight.getPosition().y;
				vertexData[offset++] = bottomRight.getPosition().z;

				//holy shit
				//vertexData[offset++] = bottomRight.getNormal().y;
				//vertexData[offset++] = bottomRight.getNormal().x;
				vertexData[offset++] = bottomRight.getNormal().x;
				vertexData[offset++] = bottomRight.getNormal().y;
				vertexData[offset++] = bottomRight.getNormal().z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;

				//top left
				vertexData[offset++] = topLeft.getPosition().x;
				vertexData[offset++] = topLeft.getPosition().y;
				vertexData[offset++] = topLeft.getPosition().z;

				vertexData[offset++] = topLeft.getNormal().x;
				vertexData[offset++] = topLeft.getNormal().y;
				vertexData[offset++] = topLeft.getNormal().z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;

				//bottom right
				vertexData[offset++] = bottomRight.getPosition().x;
				vertexData[offset++] = bottomRight.getPosition().y;
				vertexData[offset++] = bottomRight.getPosition().z;

				vertexData[offset++] = bottomRight.getNormal().x;
				vertexData[offset++] = bottomRight.getNormal().y;
				vertexData[offset++] = bottomRight.getNormal().z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;

				//top right
				vertexData[offset++] = topRight.getPosition().x;
				vertexData[offset++] = topRight.getPosition().y;
				vertexData[offset++] = topRight.getPosition().z;

				vertexData[offset++] = topRight.getNormal().x;
				vertexData[offset++] = topRight.getNormal().y;
				vertexData[offset++] = topRight.getNormal().z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 1.0f;
			}

			//Old way that uses face normals
			else {
				glm::vec3 topleft = allPoints[i][j].getPosition();
				glm::vec3 bottomleft = allPoints[i + 1][j].getPosition();
				glm::vec3 bottomright = allPoints[i + 1][j + 1].getPosition();
				glm::vec3 topright = allPoints[i][j + 1].getPosition();

				//Make sure to calculate the normals using counter-clockwise order for vertices
				glm::vec3 normal1 = Face::calcNormal(topleft, bottomleft, bottomright);
				glm::vec3 normal2 = Face::calcNormal(topleft, bottomright, topright);

				//Make sure both triangles are drawn counter-clockwise

				//top left
				vertexData[offset++] = topleft.x;
				vertexData[offset++] = topleft.y;
				vertexData[offset++] = topleft.z;

				vertexData[offset++] = normal1.x;
				vertexData[offset++] = normal1.y;
				vertexData[offset++] = normal1.z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;

				//bottom left
				vertexData[offset++] = bottomleft.x;
				vertexData[offset++] = bottomleft.y;
				vertexData[offset++] = bottomleft.z;

				vertexData[offset++] = normal1.x;
				vertexData[offset++] = normal1.y;
				vertexData[offset++] = normal1.z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 0.0f;

				//bottom right
				vertexData[offset++] = bottomright.x;
				vertexData[offset++] = bottomright.y;
				vertexData[offset++] = bottomright.z;

				vertexData[offset++] = normal1.x;
				vertexData[offset++] = normal1.y;
				vertexData[offset++] = normal1.z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;

				//top left
				vertexData[offset++] = topleft.x;
				vertexData[offset++] = topleft.y;
				vertexData[offset++] = topleft.z;

				vertexData[offset++] = normal2.x;
				vertexData[offset++] = normal2.y;
				vertexData[offset++] = normal2.z;

				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;

				//bottom right
				vertexData[offset++] = bottomright.x;
				vertexData[offset++] = bottomright.y;
				vertexData[offset++] = bottomright.z;

				vertexData[offset++] = normal2.x;
				vertexData[offset++] = normal2.y;
				vertexData[offset++] = normal2.z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;

				//top right
				vertexData[offset++] = topright.x;
				vertexData[offset++] = topright.y;
				vertexData[offset++] = topright.z;

				vertexData[offset++] = normal2.x;
				vertexData[offset++] = normal2.y;
				vertexData[offset++] = normal2.z;

				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 1.0f;
			}
		}
	}
	
	return vertexData;

}

void Cloth::manageKeyboardInput(GLFWwindow * window)
{
	//button just got clicked
	if ((glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) && !buttonDown) {
		buttonDown = true;
		useVertexNormals = !useVertexNormals;
		std::cout << "switching mode" << std::endl;
	}
	//button just got released
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE && buttonDown) {
		buttonDown = false;
	}
}
