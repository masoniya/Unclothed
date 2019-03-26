#include "Cloth.h"
#include <iostream>


Cloth::Cloth(glm::vec3 top_left, int num_cols, int num_rows, float width, float height)
{
	init(top_left, num_cols, num_rows, width, height);
}


Cloth::~Cloth()
{
}

void Cloth::init(glm::vec3 top_left,int num_cols , int num_rows, float width,float height)
{
	
	//initialize the particles array


	allPoints = new PointMass*[num_rows];

	for (int i = 0; i < num_rows; i++) {

		allPoints[i] = new PointMass[num_cols];

	}

	//initialize positions for particles
	for (int i = 0; i < num_rows; i++) {

		for (int j = 0; j < num_cols; j++) {

			std::cout << " x= " << top_left.x + (float)j / num_cols * width<< " y= " << top_left.y - (float)i / num_rows * height<<",";
			allPoints[i][j].setPosition(glm::vec3(top_left.x + (float)j/num_cols *width , top_left.y - (float)i/num_rows *height,top_left.z));
			points.push_back(&allPoints[i][j]);

		}
		std::cout << "\n";
	}
	for (int i = 0; i < num_rows; i++) {

		for (int j = 0; j < num_cols; j++) {

			allPoints[i][j].printPos();

		}
		std::cout << "\n";
	}


	// add springs

	for (int i = 0; i < num_rows; i++) {

		for (int j = 0; j < num_cols; j++) {

			// structural springs
			if (j + 1 < num_cols)
			{
				allSprings.push_back(new Spring(structural_const, structural_damp, &allPoints[i][j], &allPoints[i][j + 1]));
			}
			if (i + 1 < num_rows) {
				allSprings.push_back(new Spring(structural_const, structural_damp, &allPoints[i][j], &allPoints[i + 1][j]));
			}
			//shear springs
			if (i + 1 < num_rows ) {

				if (j + 1 < num_cols) {
					allSprings.push_back(new Spring(shearing_const, shearing_damp, &allPoints[i][j], &allPoints[i + 1][j + 1]));
				}

				if (j - 1 >= 0) {
					allSprings.push_back(new Spring(shearing_const, shearing_damp, &allPoints[i][j], &allPoints[i + 1][j - 1]));
				}

			}

			//bending springs
			if (j + 2< num_cols)
			{
				allSprings.push_back(new Spring(structural_const, structural_damp, &allPoints[i][j], &allPoints[i][j + 2]));
			}
			if (i + 2 < num_rows) {
				allSprings.push_back(new Spring(structural_const, structural_damp, &allPoints[i][j], &allPoints[i + 2][j]));
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



	

}

void Cloth::update(float deltaTime)
{
	//apply external forces
	for (ForceGenerator* force : externalForces) {

		force->applyForce();

	}

	//apply internal forces
	for (Spring* spring : allSprings) {
		spring->applyForce();

	}

	solver->solve(deltaTime);

}
