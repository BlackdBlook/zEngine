#include "GLLib.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
void GLLib::GLInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

GLFWwindow* GLLib::CreateWindow(int width, int height)
{
	GLFWwindow* window = glfwCreateWindow
		(width,height,"OpenGLEngine", NULL, NULL);
	if (window == nullptr)
	{
		throw new std::exception("null window");
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
    return window;
}

void GLLib::processECSInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void GLLib::framebuffer_size_callback
	(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLLib::GLADinit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw new std::exception();
	}
}