#version 440 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	
	float shininess;
};

struct DirLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

struct PointLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 position;
	vec3 direction;
	
	float constant;
	float linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
};

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoords;

out vec4 FragColor;

#define dirLightCount 1
#define pointLightCount 4
#define spotLightCount 1

uniform Material material;
uniform DirLight dirLights[dirLightCount];
uniform PointLight pointLights[pointLightCount];
uniform SpotLight spotLights[spotLightCount];
uniform vec3 viewPosition;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(fragNormal);
	vec3 viewDir = normalize(viewPosition - fragPos);

	vec3 resultColor;
	
	for(int i = 0; i < dirLightCount; i++){
		resultColor += calcDirLight(dirLights[i], norm, viewDir);
	}
	
	for(int i = 0; i < pointLightCount; i++){
		resultColor += calcPointLight(pointLights[i], norm, fragPos, viewDir);
	}
	
	for(int i = 0; i < spotLightCount; i++){
		resultColor += calcSpotLight(spotLights[i], norm, fragPos, viewDir);
	}
	
	FragColor = vec4(resultColor, 1.0);
}

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	
	return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//attenuation
	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	return ambient + diffuse + specular;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	//specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//attenuation
	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	//soft edges and clamping
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon , 0.0, 1.0);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));
	
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	diffuse *= intensity;
	specular *= intensity;
	
	return ambient + diffuse + specular;
}
