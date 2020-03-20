// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Timer.h"


#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"


#define WIN_W 1280
#define WIN_H 720


static void ErrorCallback(int error,const char* message)
{
	fprintf(stderr, "Error: %s\n", message);
}

static void GLDebugOutputCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
 
printf("GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);

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


	///////////  Calling OpenGL API is fine from here




	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugOutputCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);


	const uint32_t bufferBindIndex = 0;

	const uint32_t posAttribIndex = 0;
	const uint32_t uvAttribIndex = 1;
	const uint32_t normalAttribIndex = 2;
	const uint32_t numVertices = 4;

	//Create and configure our vertex buffer
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uvs;
		glm::vec3 normals;
	};

	Vertex vertices[numVertices] = {
		{glm::vec3(0.5f,0.5f,0.0f),glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,0.5f,0.0f),glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,-0.5f,0.0f),glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)}	
	};

 

	GLuint  vertexArrayObject, vertexBufferObject;

	glCreateVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glCreateBuffers(1, &vertexBufferObject);
	glBindVertexBuffer(bufferBindIndex, vertexBufferObject, 0, sizeof(Vertex));
	glNamedBufferStorage(vertexBufferObject, numVertices * sizeof(Vertex), vertices, GL_MAP_WRITE_BIT);

	glEnableVertexAttribArray(posAttribIndex);
	glEnableVertexAttribArray(uvAttribIndex);
	glEnableVertexAttribArray(normalAttribIndex);

	//position attribute
	glVertexAttribFormat(posAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexAttribBinding(posAttribIndex, bufferBindIndex);

	//uvs attribute
	glVertexAttribFormat(uvAttribIndex, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uvs));
	glVertexAttribBinding(uvAttribIndex, bufferBindIndex);

	//normals attribute
	glVertexAttribFormat(normalAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normals));
	glVertexAttribBinding(normalAttribIndex, bufferBindIndex);



	const char* vertShaderStr = R"(#version 450
     
      layout(location = 0) in vec3 pos;
      layout(location = 1) in vec2 uvs;
      layout(location = 2) in vec3 normals;
      void main()
       {
 
          gl_Position  = vec4(pos,1.0);
       }

     )";


	const char* fragShaderStr = R"(#version 450
     
      out vec4 PIXEL;
      void main()
       {
 
          PIXEL = vec4(0.0,1.0,0.0,1.0);
       }
     )";


	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint prog = glCreateProgram();
	glShaderSource(vertShader, 1,&vertShaderStr,NULL);
	glCompileShader(vertShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
	if (GL_FALSE == isCompiled)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog =(char*) malloc(maxLength);
		glGetShaderInfoLog(vertShader, maxLength, &maxLength, &infoLog[0]);

		printf("Vertex shader failed to compile with error: %s\n", infoLog);
		free(infoLog);
		// We don't need the shader anymore.
		glDeleteShader(vertShader);
	}


	glShaderSource(fragShader, 1, &fragShaderStr, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
	if (GL_FALSE == isCompiled)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char* infoLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(fragShader, maxLength, &maxLength, &infoLog[0]);

		printf("Fragment shader failed to compile with error: %s\n", infoLog);
		free(infoLog);
		// We don't need the shader anymore.
		glDeleteShader(fragShader);
	}


	glAttachShader(prog, vertShader);
	glAttachShader(prog, fragShader);
	glLinkProgram(prog);
	glDetachShader(prog, vertShader);
	glDetachShader(prog, fragShader);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);


	//Here is the start of our naive render loop
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(win))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//here we render...

		glUseProgram(prog);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	//start termination
	glfwDestroyWindow(win);
	glfwTerminate();

  
	printf("Time total on exit %f seconds\n", timer.getElapsedTimeInSec() - tStart);
	return EXIT_SUCCESS;
}


