#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	coords.setCoords(x, y, z);
}

void Vertex::setCoords(float x, float y, float z)
{
	coords.setCoords(x, y, z);
}

Coords Vertex::getCoords()
{
	return Coords();
}
