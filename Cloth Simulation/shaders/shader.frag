#version 440 core
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
};

out vec4 FragColor;

//in vec4 vertexColor;
//in vec2 texCoords;

//uniform sampler2D textureSampler;
//uniform sampler2D textureSampler2;

in vec3 normal;
in vec3 fragPos;

uniform Material material;
uniform Light light;

uniform vec3 viewPosition;

void main()
{
	//ambient lighting
	vec3 ambient = light.ambient * material.ambient;
	
	//diffuse lighting
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	//specular lighting
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);
	
	vec3 resultColor = ambient + diffuse + specular;
	FragColor = vec4(resultColor, 1.0);
    //FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f);
	//vec2 flipped = vec2(1 - texCoords.x, texCoords.y);
	//FragColor = mix(texture(textureSampler, texCoords), texture(textureSampler2, flipped), 0.9);
}
