#version 440 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoords;

uniform sampler2D textureSampler;

void main()
{
    //FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
	FragColor = texture(textureSampler, texCoords) * vertexColor;
}