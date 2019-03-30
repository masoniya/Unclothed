#pragma once

#include <glfw/glfw3.h>


class FpsCounter
{
public:
	FpsCounter();
	~FpsCounter();

	float fps;

	void update();

private:
	unsigned int fpsSamples;

	float *recentFrameTimes;
	float prevTime;

	unsigned int currentFrame;
};
