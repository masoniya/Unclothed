#version 440 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoords;

uniform sampler2D textureSampler;
uniform sampler2D textureSampler2;

void main()
{
    //FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
	vec2 flipped = vec2(1 - texCoords.x, texCoords.y);
	FragColor = mix(texture(textureSampler, texCoords), texture(textureSampler2, flipped), 0.9);
}	