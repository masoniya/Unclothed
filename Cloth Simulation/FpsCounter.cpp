#include "FpsCounter.h"


float deltaTime = 0.0f;

FpsCounter::FpsCounter() : fpsSamples(100), prevTime(0.0f), fps(0.0f), currentFrame(0)
{
	recentFrameTimes = new float[fpsSamples]();
}

void FpsCounter::update() 
{
	float currentTime = (float)glfwGetTime();
	deltaTime = currentTime - prevTime;
	prevTime = currentTime;

	recentFrameTimes[currentFrame++ % fpsSamples] = deltaTime;

	float total = 0.0f;
	for (unsigned int i = 0; i < fpsSamples; i++) {
		total += recentFrameTimes[i];
	}
	float avgFrameTime = total / fpsSamples;
	fps = 1.0f / avgFrameTime;

}

FpsCounter::~FpsCounter()
{
	delete recentFrameTimes;
}
