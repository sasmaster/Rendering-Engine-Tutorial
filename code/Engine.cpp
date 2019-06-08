// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 
#include <stdlib.h>
#include <stdio.h>
#include "Timer.h"
#include "GLFW/glfw3.h"

int main()
{
	Timer t;
	t.start();

	

	if (!glfwInit())
	{
		printf("Failed to init GLFW\n");
		exit(EXIT_FAILURE);
	}

	GLFWwindow* win = glfwCreateWindow(1280, 720, "Simple window", nullptr, nullptr);

	return EXIT_SUCCESS;
}

 
