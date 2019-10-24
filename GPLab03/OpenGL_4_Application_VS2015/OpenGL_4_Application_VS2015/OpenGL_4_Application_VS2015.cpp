//
//  main.cpp
//  OpenGL_Shader_Example_step1
//
//  Created by CGIS on 30/11/15.
//  Copyright © 2015 CGIS. All rights reserved.
//

#define GLEW_STATIC

#include <iostream>
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include <string>
#include "Shader.hpp"

int glWindowWidth = 640;
int glWindowHeight = 480;
int retina_width, retina_height;
GLFWwindow* glWindow = NULL;
int amount = 0, amount2=0;

//vertex coordinates in normalized device coordinates
GLfloat vertexData[] = {//vertex position and vertex color
	-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.7f, 0.0f, 0.5f, 0.5f, 0.5f
};

GLuint vertexIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 3, 4
};

GLuint verticesVBO;
GLuint verticesEBO;
GLuint objectVAO;

gps::Shader myCustomShader;

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	fprintf(stdout, "window resized to width: %d , and height: %d\n", width, height);
	//TODO
}

void initObjects()
{
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &verticesEBO); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesEBO); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW);

	//vertex position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

bool initOpenGLWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	//for Mac OS X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glWindow = glfwCreateWindow(glWindowWidth, glWindowHeight, "OpenGL Shader Example", NULL, NULL);
	if (!glWindow) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(glWindow, windowResizeCallback);
	glfwMakeContextCurrent(glWindow);

	glfwWindowHint(GLFW_SAMPLES, 4);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	//for RETINA display
	glfwGetFramebufferSize(glWindow, &retina_width, &retina_height);

	return true;
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glViewport(0, 0, retina_width, retina_height);

	if (glfwGetKey(glWindow, GLFW_KEY_A)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_D)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_LEFT)) {
		amount--;
		GLint uniformVertexLocation = glGetUniformLocation(myCustomShader.shaderProgram, "uniformPos");
		glUniform3f(uniformVertexLocation, amount*0.05f, amount2*0.05f, 0.0f);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_RIGHT)) {
		amount++;
		GLint uniformVertexLocation = glGetUniformLocation(myCustomShader.shaderProgram, "uniformPos");
		glUniform3f(uniformVertexLocation, amount*0.05f, amount2*0.05f, 0.0f);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_UP)) {
		amount2++;
		GLint uniformVertexLocation = glGetUniformLocation(myCustomShader.shaderProgram, "uniformPos");
		glUniform3f(uniformVertexLocation, amount*0.05f, amount2*0.05f, 0.0f);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_DOWN)) {
		amount2--;
		GLint uniformVertexLocation = glGetUniformLocation(myCustomShader.shaderProgram, "uniformPos");
		glUniform3f(uniformVertexLocation, amount*0.05f, amount2*0.05f, 0.0f);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE))
	{
		exit(0);
	}

	myCustomShader.useShaderProgram();

	glBindVertexArray(objectVAO);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}


int main(int argc, const char * argv[]) {

	initOpenGLWindow();

	initObjects();
	myCustomShader.loadShader("shaders/shaderStart.vert", "shaders/shaderStart.frag");
	myCustomShader.useShaderProgram();
	GLint uniformColourLocation = glGetUniformLocation(myCustomShader.shaderProgram, "uniformColour"); 
	glUniform3f(uniformColourLocation, 0.15f, 0.0f, 0.84);

	while (!glfwWindowShouldClose(glWindow)) {
		renderScene();

		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}

	//close GL context and any other GLFW resources
	glfwTerminate();

	return 0;
}
