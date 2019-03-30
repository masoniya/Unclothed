#include <iostream>

#include "FpsCounter.h"


float deltaTime = 0.0f;

FpsCounter::FpsCounter() : fpsSamples(100), prevTime(0.0f), fps(0.0f), currentFrame(0), frameSinceLastReport(0), printFps(true)
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

	if (printFps && frameSinceLastReport++ > fps) {
		std::cout << "fps : " << fps << std::endl;
		frameSinceLastReport = 0;
	}
}

void FpsCounter::disablePrinting()
{
	printFps = false;
}

void FpsCounter::enablePrinting()
{
	printFps = true;
}

FpsCounter::~FpsCounter()
{
	delete recentFrameTimes;
}
