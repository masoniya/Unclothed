#include "SpotLight.h"


SpotLight::SpotLight() :
	tempCutOff(1.0f),
	tempOuterCutOff(1.0f)
{
}

SpotLight::SpotLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor,
	glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, Attenuation attenuation) :
	LightSource(ambientColor, diffuseColor, specularColor),
	tempCutOff(1.0f),
	tempOuterCutOff(1.0f)
{
	this->position = position;
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
	this->attenuation = attenuation;
}

void SpotLight::manageKeyboardInput(GLFWwindow * window)
{

	if ((glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) && !buttonDown) {
		buttonDown = true;
		//swap cutOff
		float temp = cutOff;
		cutOff = tempCutOff;
		tempCutOff = temp;

		//swap outerCutOff
		temp = outerCutOff;
		outerCutOff = tempOuterCutOff;
		tempOuterCutOff = temp;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && buttonDown) {
		buttonDown = false;
	}
}
