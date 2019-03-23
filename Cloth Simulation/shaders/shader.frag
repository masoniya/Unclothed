#version 440 core

struct Material{
	//ambient is usually same color as diffuse
	//vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	
	float shininess;
};

struct Light{
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
in vec3 normal;
in vec2 texCoords;

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 viewPosition;

void main()
{
	//ambient lighting
	vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;
	
	//diffuse lighting
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction); //this is ignored for now until we figure out multiple lights
	lightDir = normalize(light.position - fragPos); 
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;
	
	//specular lighting
	vec3 viewDir = normalize(viewPosition - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;
	
	//spotlight (soft edges)
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon , 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;
	
	/*
	if(theta > light.cutOff)
	{
		FragColor = vec4(resultColor, 1.0);
	}
	else
	{
		FragColor = vec4(light.ambient  * vec3(texture(material.diffuse, texCoords)), 1.0);
	}
	*/
	
	//attenuation
	float dist = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	vec3 resultColor = ambient + diffuse + specular;
	FragColor = vec4(resultColor, 1.0);
}
