#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <vector>
#include <algorithm>

#include "Shader.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "VBO.hpp"
#include "Texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Vertices coordinates
GLfloat vertices[] { //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};
// Indices for vertices order
GLuint indices[] {
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
	// SETUP WINDOW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Raphaele's Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// SETUP GLAD (manages function pointers for OpenGL)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	// Whenever the GLFW window resizes (callback), adjust viewport

	// SHADER
	Shader shaderProgram("default.vert", "default.frag");

	// SETUP VERTEX DATA (BUFFER) & CONFIG VERTEX ATTRIBUTES
	VAO VAO1;
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);	// vertex position
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));	// vertex color
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));	// texture coord
	VAO1.Unbind();
	EBO1.Unbind();

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// draw in wireframe polygons.

	// Texture
	Texture wallTex("Textures/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Texture faceTex("Textures/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	wallTex.texUnit(shaderProgram, "tex0", 0);
	faceTex.texUnit(shaderProgram, "tex1", 1);

	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render
		shaderProgram.Activate();
		wallTex.Bind();
		faceTex.Bind();

		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		// glfw: swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// CLEANUP
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	wallTex.Delete();
	faceTex.Delete();
	shaderProgram.Delete();
	glfwTerminate();
	return 0;
}


static void framebuffer_size_callback(GLFWwindow* window, int w, int h) { glViewport(0, 0, w, h); }
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
}