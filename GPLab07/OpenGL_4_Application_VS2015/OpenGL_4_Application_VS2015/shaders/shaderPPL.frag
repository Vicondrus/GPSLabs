#version 410 core

uniform vec3 baseColor;
//matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

in vec3 vPos;
in vec3 vNorm;

//lighting
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 specularColor;

vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float specularStrength = 0.5f;

out vec4 fColor;

void computeLight()
{
	//compute eye space coordinates
	vec4 vertPosEye = view * model * vec4(vPos, 1.0f);
	vec3 normalEye = normalize(normalMatrix * vNorm);
	
	//normalize light direction
	vec3 lightDirN = normalize(lightDir);
	
	//compute view direction (in eye coordinates, the viewer is situated at the origin
	vec3 viewDir = normalize(- vertPosEye.xyz);
	
	//compute ambient light
	ambient = ambientStrength * lightColor;
	
	//compute diffuse light
	diffuse = max(dot(normalEye, lightDirN), 0.0f) * lightColor;
	
	//compute specular light
	vec3 reflectDir = reflect(-lightDirN, normalEye);
	float specCoeff = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
	specular = specularStrength * specCoeff * lightColor;
}

void main()
{	
	computeLight();
	
	//compute final vertex color
	vec3 color = min(ambient * ambientColor + diffuse * baseColor + specular * specularColor, 1.0f);
	fColor = vec4(color, 1.0f);
}
