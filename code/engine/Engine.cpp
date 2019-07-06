// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Timer.h"


#include "glad/glad.h"
#include "GLFW/glfw3.h"


#define WIN_W 1280
#define WIN_H 720


static void ErrorCallback(int error,const char* message)
{
	fprintf(stderr, "Error: %s\n", message);
}
 
int main()
{
	Timer timer;
	timer.start();
	const double tStart = timer.getElapsedTimeInSec();

	 
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		printf("Failed to init GLFW\n");
		exit(EXIT_FAILURE);
	}

	//configure OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//pixel format config 

	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // _DEBUG

	glfwWindowHint(GLFW_SAMPLES, 8);//MSAA


	GLFWwindow* win = glfwCreateWindow(WIN_W, WIN_H, "Simple Engine", nullptr, nullptr);
	assert(win);

	glfwMakeContextCurrent(win);


	//GL API init

	if (!gladLoadGL())
	{
		printf("Failed to load GL API\n");
		exit(EXIT_FAILURE);
	}



	//Here is the start of our naive render loop
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(win))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//here we render...


		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	//start termination
	glfwDestroyWindow(win);
	glfwTerminate();

  
	printf("Time total on exit %f seconds\n", timer.getElapsedTimeInSec() - tStart);
	return EXIT_SUCCESS;
}


