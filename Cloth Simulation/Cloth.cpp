#include <iostream>

#include "Cloth.h"
#include "SemiImpEuler.h"


extern float deltaTime;

Cloth::Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height, float mass)
{
	init(top_left, num_cols, num_rows, width, height, mass);
}


void Cloth::init(glm::vec3 top_left, int num_cols, int num_rows, float width, float height, float mass)
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

}

void Cloth::update(float deltaTime)
{
	//apply internal forces (~ 4ms)
	for (Spring* spring : allSprings) {
		spring->applyForce();
	}

	//(~ 0.3ms)
	solver->solve(deltaTime);
}

float * Cloth::getVertexData()
{
	int offset = 0;

	bool calculateTexCoords = true;
	bool weird = false;
	float repeatTileCount = 2.0f;

	float texCoordXStep = 1.0f / (width - 1) * repeatTileCount;
	float texCoordYStep = 1.0f / (height - 1) * repeatTileCount;


	//calculate face normals (~ 1.2ms)
	//double beforeNormal = glfwGetTime();
	for (Face *face : faces) {
		//(~ 0.8ms)
		face->calcNormal();
		//(~ 0.8ms)
		face->updatePointNormals();
	}

	//double afterNormal = glfwGetTime();
	//calculate point normals (~ 0.8ms)
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			allPoints[i][j].calculatePointNormal();
		}
	}
	//double afterAverage = glfwGetTime();

	//double start = glfwGetTime();
	//(! 0.2ms)
	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width - 1; j++) {

			glm::vec3 topLeftPos = allPoints[i][j].getPosition();
			glm::vec3 bottomLeftPos = allPoints[i + 1][j].getPosition();
			glm::vec3 bottomRightPos = allPoints[i + 1][j + 1].getPosition();
			glm::vec3 topRightPos = allPoints[i][j + 1].getPosition();
				
			glm::vec3 topLeftNormal = allPoints[i][j].getNormal();
			glm::vec3 bottomLeftNormal = allPoints[i + 1][j].getNormal();
			glm::vec3 bottomRightNormal = allPoints[i + 1][j + 1].getNormal();
			glm::vec3 topRightNormal = allPoints[i][j + 1].getNormal();

			//top left
			vertexData[offset++] = topLeftPos.x;
			vertexData[offset++] = topLeftPos.y;
			vertexData[offset++] = topLeftPos.z;

			vertexData[offset++] = topLeftNormal.x;
			vertexData[offset++] = topLeftNormal.y;
			vertexData[offset++] = topLeftNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j) * texCoordXStep;
					vertexData[offset++] = 1 - (i) * texCoordYStep;
				}
				else {
					vertexData[offset++] = topLeftPos.x;
					vertexData[offset++] = topLeftPos.y;
				}
					
			}
				
			//bottom left
			vertexData[offset++] = bottomLeftPos.x;
			vertexData[offset++] = bottomLeftPos.y;
			vertexData[offset++] = bottomLeftPos.z;

			vertexData[offset++] = bottomLeftNormal.x;
			vertexData[offset++] = bottomLeftNormal.y;
			vertexData[offset++] = bottomLeftNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 0.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j) * texCoordXStep;
					vertexData[offset++] = 1 - (i + 1) * texCoordYStep;
				}
				else {
					vertexData[offset++] = bottomLeftPos.x;
					vertexData[offset++] = bottomLeftPos.y;
				}
			}
				
			//bottom right
			vertexData[offset++] = bottomRightPos.x;
			vertexData[offset++] = bottomRightPos.y;
			vertexData[offset++] = bottomRightPos.z;

			vertexData[offset++] = bottomRightNormal.x;
			vertexData[offset++] = bottomRightNormal.y;
			vertexData[offset++] = bottomRightNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j + 1) * texCoordXStep;
					vertexData[offset++] = 1 - (i + 1) * texCoordYStep;
				}
				else {
					vertexData[offset++] = bottomRightPos.x;
					vertexData[offset++] = bottomRightPos.y;
				}
			}
				
			//top left
			vertexData[offset++] = topLeftPos.x;
			vertexData[offset++] = topLeftPos.y;
			vertexData[offset++] = topLeftPos.z;

			vertexData[offset++] = topLeftNormal.x;
			vertexData[offset++] = topLeftNormal.y;
			vertexData[offset++] = topLeftNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 0.0f;
				vertexData[offset++] = 1.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j) * texCoordXStep;
					vertexData[offset++] = 1 - (i) * texCoordYStep;
				}
				else {
					vertexData[offset++] = topLeftPos.x;
					vertexData[offset++] = topLeftPos.y;
				}
			}
				
			//bottom right
			vertexData[offset++] = bottomRightPos.x;
			vertexData[offset++] = bottomRightPos.y;
			vertexData[offset++] = bottomRightPos.z;

			vertexData[offset++] = bottomRightNormal.x;
			vertexData[offset++] = bottomRightNormal.y;
			vertexData[offset++] = bottomRightNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 0.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j + 1) * texCoordXStep;
					vertexData[offset++] = 1 - (i + 1) * texCoordYStep;
				}
				else {
					vertexData[offset++] = bottomRightPos.x;
					vertexData[offset++] = bottomRightPos.y;
				}
			}
				
			//top right
			vertexData[offset++] = topRightPos.x;
			vertexData[offset++] = topRightPos.y;
			vertexData[offset++] = topRightPos.z;

			vertexData[offset++] = topRightNormal.x;
			vertexData[offset++] = topRightNormal.y;
			vertexData[offset++] = topRightNormal.z;

			if (!calculateTexCoords) {
				vertexData[offset++] = 1.0f;
				vertexData[offset++] = 1.0f;
			}
			else {
				if (!weird) {
					vertexData[offset++] = (j + 1) * texCoordXStep;
					vertexData[offset++] = 1 - (i) * texCoordYStep;
				}
				else {
					vertexData[offset++] = topRightPos.x;
					vertexData[offset++] = topRightPos.y;
				}
			}

		}
	}

	//double end = glfwGetTime();
	/*static double secondCounter = 0.0;
	secondCounter += deltaTime;
	if (secondCounter > 1.0) {
		secondCounter -= 1.0;
		std::cout << "Normal Calculation Time : " << (afterNormal - beforeNormal) * 1000 << std::endl;
		std::cout << "Normal Averaging Time : " << (afterAverage - afterNormal) * 1000 << std::endl;
		std::cout << "Vertex Data Time : " << (end - start) * 1000 << std::endl;
	}*/
	
	return vertexData;

}
