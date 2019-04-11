#pragma once

class Render
{
public:
	virtual void initcloth(float * vertexData, int size) = 0;

	virtual void updatecloth(float * vertexData, int size) = 0;
};
