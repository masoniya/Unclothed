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
uniform vec3 viewPosition;

uniform float ambientStrength;
uniform float specularStrength;

uniform int shininess;

void main()
{
	//ambient lighting
	vec3 ambient = ambientStrength * lightColor;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	
	//diffuse lighting
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	//specular lighting
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 resultColor = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(resultColor, 1.0);
    //FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
	//vec2 flipped = vec2(1 - texCoords.x, texCoords.y);
	//FragColor = mix(texture(textureSampler, texCoords), texture(textureSampler2, flipped), 0.9);
}
