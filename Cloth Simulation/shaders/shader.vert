#version 440 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
//layout (location = 2) in vec2 texCoord;

out vec4 vertexColor;
//out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	//gl_Position = vec4(pos, 1.0f);
	vertexColor = vec4(col, 1.0);
	//texCoords = texCoord;
}
