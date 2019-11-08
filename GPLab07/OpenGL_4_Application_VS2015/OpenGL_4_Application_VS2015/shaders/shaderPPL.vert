#version 410 core

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;

//matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vPos;
out vec3 vNorm;

void main()
{	
	
	vPos = vPosition;
	vNorm = vNormal;
	gl_Position = projection * view * model * vec4(vPosition, 1.0f);
} 
