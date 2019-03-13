#pragma once
#include <vector>

#include <glfw/glfw3.h>

#include "KeyboardControl.h"
#include "MouseControl.h"

class InputManager
{
public:
	InputManager(GLFWwindow *window);

	void registerKeyboardInput(KeyboardControl * inputObject);

	void handleKeyboardInput();

	//In retrospect maybe the entire input manager should have been static but w/e
	static void registerMouseInput(MouseControl * inputObject);

	static void handleMouseInput(double xPosition, double yPosition);

private:
	GLFWwindow *window;

	std::vector<KeyboardControl *> keyboardInputObjects;

	static MouseControl * activeMouseInputObject;

	static double mouseLastXPos;
	static double mouseLastYPos;

	static float mouseSensitivity;
};
