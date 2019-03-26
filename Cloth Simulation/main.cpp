#include <iostream>

//#include "Engine.h"

#include "Cloth.h"

int main(int argc, char** argv) {

	/*Engine engine;

	try {
		engine.start();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		getchar();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;*/


	Cloth* cloth = new Cloth(glm::vec3(0.5, 0.5, 0), 10, 10, 0.5, 0.5);

	getchar();
	
	std::cout << "";
	
}
