#include "InputManager.h"

#include <iostream>

static void mouse_callback(GLFWwindow* window, double xPosition, double yPosition);

MouseControl * InputManager::activeMouseInputObject;
double InputManager::mouseLastXPos;
double InputManager::mouseLastYPos;
float InputManager::mouseSensitivity = 0.05f;

InputManager::InputManager(GLFWwindow * window)
{
	this->window = window;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
}

void InputManager::registerKeyboardInput(KeyboardControl * inputObject)
{
	keyboardInputObjects.push_back(inputObject);
}

void InputManager::handleKeyboardInput()
{
	for (KeyboardControl *in : keyboardInputObjects) {
		in->manageKeyboardInput(window);
	}
}

//sets the active mouse controlled object (for now only one object can be mouse controlled but this can change later
void InputManager::registerMouseInput(MouseControl * inputObject)
{
	activeMouseInputObject = inputObject;
}

//sends the change in x and y positions
void InputManager::handleMouseInput(double xPosition, double yPosition)
{
	static bool firstMouseUse = true;
	if (firstMouseUse) {
		mouseLastXPos = xPosition;
		mouseLastYPos = yPosition;
		firstMouseUse = false;
	}

	double xOffset = xPosition - mouseLastXPos;
	double yOffset = mouseLastYPos - yPosition;		//reversed since y-coords are bottom to top
	mouseLastXPos = xPosition;
	mouseLastYPos = yPosition;

	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	//Send the offsets to the mouse controlled object (camera)
	activeMouseInputObject->manageMouseInput(xOffset, yOffset);
}


void mouse_callback(GLFWwindow * window, double xPosition, double yPosition)
{
	InputManager::handleMouseInput(xPosition, yPosition);
}
