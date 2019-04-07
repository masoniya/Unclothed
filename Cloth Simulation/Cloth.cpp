#include "Cloth.h"
#include <iostream>
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

	//this->vertexData = new float[(width - 1)*(height - 1) * 8 * 6];

	allPoints = new PointMass*[num_rows];

	for (int i = 0; i < num_rows; i++) {

		allPoints[i] = new PointMass[num_cols];

	}

	//initialize positions for particles
	for (int i = 0; i < num_rows; i++) {

		for (int j = 0; j < num_cols; j++) {

			float newX = top_left.x + ((float)j / num_cols) *width;
			float newY = top_left.y ;
			float newZ = top_left.z + ((float)i / num_rows) *height;
			allPoints[i][j].setPosition(glm::vec3(newX , newY, newZ));
			allPoints[i][j].setMass(mass/width*height);


			if  (i == 0 && j==0) {
				allPoints[i][j].setImmovable();
			}
			if (i == 0 && j == num_cols - 1) {
				allPoints[i][j].setImmovable();

			}

			/*if (i == num_rows-1 && j == 0) {
				allPoints[i][j].setImmovable();
			}
			if (i == num_rows-1 && j == num_cols-1) {
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
			if (j + 1 < num_cols)
			{
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
			if (j + 2< num_cols)
			{
				allSprings.push_back(new Spring(k_const_bending, damp, &allPoints[i][j], &allPoints[i][j + 2]));
			}
			if (i + 2 < num_rows) {
				allSprings.push_back(new Spring(k_const_bending, damp, &allPoints[i][j], &allPoints[i + 2][j]));
			}

		}

	}
	

	// add the faces

	for (int i = 0; i < num_rows-1; i++) {

		for (int j = 0; j < num_cols-1; j++) {

			Face* face = new Face(&allPoints[i][j], &allPoints[i + 1][j], &allPoints[i + 1][j + 1]);
			Face* face1 = new Face(&allPoints[i][j], &allPoints[i][j+1], &allPoints[i + 1][j + 1]);

			faces.push_back(face);
			faces.push_back(face1);
			

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
	

	//apply internal forces
	for (Spring* spring : allSprings) {
		spring->applyForce();

	}

	solver->solve(deltaTime);

}

float * Cloth::getVertexData()
{
	float * vertexData = new float[(width-1)*(height-1)*8*6];
	int offset = 0;

	for (int i = 0; i < height-1; i++) {

		for (int j = 0; j < width-1; j++) {

			glm::vec3 topleft = allPoints[i][j].getPosition();
			glm::vec3 bottomleft = allPoints[i+1][j].getPosition();
			glm::vec3 bottomright = allPoints[i+1][j+1].getPosition();
			glm::vec3 topright = allPoints[i][j+1].getPosition();

			glm::vec3 normal1 = Face::calcNormal(topleft, bottomright,bottomleft);

			glm::vec3 normal2 = Face::calcNormal(topleft, topright, bottomright);



			//top left
			vertexData[offset++] = topleft.x;
			vertexData[offset++] = topleft.y;
			vertexData[offset++] = topleft.z;

			vertexData[offset++] = normal1.x;
			vertexData[offset++] = normal1.y;
			vertexData[offset++] = normal1.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/

			vertexData[offset++] = 0.0f;
			vertexData[offset++] = 1.0f;

			//bottom left
			vertexData[offset++] = bottomleft.x;
			vertexData[offset++] = bottomleft.y;
			vertexData[offset++] = bottomleft.z;

			vertexData[offset++] = normal1.x;
			vertexData[offset++] = normal1.y;
			vertexData[offset++] = normal1.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/

			vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;

			//bottom right
			vertexData[offset++] = bottomright.x;
			vertexData[offset++] = bottomright.y;
			vertexData[offset++] = bottomright.z;

			vertexData[offset++] = normal1.x;
			vertexData[offset++] = normal1.y;
			vertexData[offset++] = normal1.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/

			vertexData[offset++] = 1.0f;
			vertexData[offset++] = 0.0f;

			//top left
			vertexData[offset++] = topleft.x;
			vertexData[offset++] = topleft.y;
			vertexData[offset++] = topleft.z;

			vertexData[offset++] = normal2.x;
			vertexData[offset++] = normal2.y;
			vertexData[offset++] = normal2.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/


			vertexData[offset++] = 0.0f;
			vertexData[offset++] = 1.0f;

			//top right
			vertexData[offset++] = topright.x;
			vertexData[offset++] = topright.y;
			vertexData[offset++] = topright.z;

			vertexData[offset++] = normal2.x;
			vertexData[offset++] = normal2.y;
			vertexData[offset++] = normal2.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/


			vertexData[offset++] = 1.0f;
			vertexData[offset++] = 1.0f;

			//bottom right
			vertexData[offset++] = bottomright.x;
			vertexData[offset++] = bottomright.y;
			vertexData[offset++] = bottomright.z;

			vertexData[offset++] = normal2.x;
			vertexData[offset++] = normal2.y;
			vertexData[offset++] = normal2.z;

			/*vertexData[offset++] = 0.0f;
			vertexData[offset++] = 0.0f;
			vertexData[offset++] = -1.0f;*/

			vertexData[offset++] = 1.0f;
			vertexData[offset++] = 0.0f;
			
		}

	}
	

	return vertexData;

	
}
