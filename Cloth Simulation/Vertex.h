#pragma once

struct Coords
{
	float X;
	float Y;
	float Z;

	void setCoords(float x, float y, float z) {
		X = x; 
		Y = y; 
		Z = z;
	}
};

class Vertex
{
private:
	Coords coords;

public:
	Vertex(float x, float y, float z);

	void setCoords(float x, float y, float z);
	Coords getCoords();

};

