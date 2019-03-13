#pragma once

#include <glm/glm.hpp>

#include "KeyboardControl.h"
#include "MouseControl.h"

class Camera : public KeyboardControl, public MouseControl
{
public:
	Camera();
	Camera(glm::vec3, glm::vec3, glm::vec3);

	glm::mat4 view();

	void manageKeyboardInput(GLFWwindow *window);
	void manageMouseInput(double xOffset, double yOffset);

private:

	float cameraSpeed;

	void construct(glm::vec3, glm::vec3, glm::vec3);
	void updateView();

	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	glm::mat4 viewMatrix;

	float pitch;
	float yaw;
};
