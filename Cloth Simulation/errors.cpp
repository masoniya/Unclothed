#pragma once
#include "errors.h"

void logError(const char* message) {
	std::cout << "Error : " << message << std::endl;
}

void fatalError(const char* message) {
	std::cout << "Fatal Error : " << message << std::endl;

}
