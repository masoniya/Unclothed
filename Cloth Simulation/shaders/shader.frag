#version 440 core
out vec4 FragColor;

//in vec4 vertexColor;
//in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

//uniform sampler2D textureSampler;
//uniform sampler2D textureSampler2;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;

uniform float ambientStrength;

void main()
{
	//ambient lighting
	vec3 ambient = ambientStrength * lightColor;
	
	//diffuse lighting
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	//specular lighting

	
	vec3 resultColor = (ambient + diffuse) * objectColor;
	FragColor = vec4(resultColor, 1.0);
    //FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
	//vec2 flipped = vec2(1 - texCoords.x, texCoords.y);
	//FragColor = mix(texture(textureSampler, texCoords), texture(textureSampler2, flipped), 0.9);
}
