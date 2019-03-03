#pragma once
#include "errors.h"

void logError(const char* message) {
	std::cout << "Fatal Error : " << message << std::endl;
}
