#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

extern float deltaTime;

static const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera()
{
	construct(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
	construct(position, front, up);
}


void Camera::construct(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
	cameraSpeed = 0.005f;

	cameraPosition = position;
	cameraFront = front;
	cameraUp = up;

	pitch = 0.0f;
	yaw = -90.0f;

	updateView();
}

glm::mat4 Camera::view()
{
	return viewMatrix;
}

void Camera::manageKeyboardInput(GLFWwindow *window)
{
	cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	updateView();
}

void Camera::manageMouseInput(double xOffset, double yOffset)
{
	yaw += (float)xOffset;
	pitch += (float)yOffset;

	//restrict camera movement
	if (pitch > 89.9f) {
		pitch = 89.9f;
	}
	if (pitch < -89.9f) {
		pitch = -89.9f;
	}

	recalculateCameraVectors();

	updateView();
}

void Camera::updateView()
{
	viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::recalculateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//recalculate camera vectors
	cameraFront = glm::normalize(front);

	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, WORLD_UP));

	//cameraUp = glm::normalize(glm::cross(cameraFront, cameraRight));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
