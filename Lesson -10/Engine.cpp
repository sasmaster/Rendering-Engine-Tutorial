// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"

#include "Timer.h"

#include "RenderContext.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GraphicsAPI.h"
#include "SceneNode.h"



#define WIN_W 1280
#define WIN_H 720

using namespace sge;



 
 
int main()
{
	Timer timer;
	timer.start();
	const double tStart = timer.getElapsedTimeInSec();

	
	RenderContext renderContext(WIN_W, WIN_H, true);
	renderContext.Create();
 
	GraphicsAPI::Create();

 

	const uint32_t numVertices = 4;
	const uint32_t bufferBindIndex = 0;
	const uint32_t positionAttribIndex = 0;
	const uint32_t uvAttribIndex = 1;
	const uint32_t normalAttribIndex = 2;
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uvs;
		glm::vec3 normals;
	};

	Vertex vertices[numVertices] = {
	
		{glm::vec3(0.5f,0.5f,0.0f)  ,glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,0.5f,0.0f) ,glm::vec2(0.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,-0.5f,0.0f) ,glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)}
	
	};


	GLuint vertexArrayObject, vertexBufferObject;

	glCreateVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glCreateBuffers(1, &vertexBufferObject);
	glBindVertexBuffer(bufferBindIndex, vertexBufferObject, 0, sizeof(Vertex));
	glNamedBufferStorage(vertexBufferObject, numVertices * sizeof(Vertex), vertices, GL_MAP_WRITE_BIT);


	glEnableVertexAttribArray(positionAttribIndex);
	glEnableVertexAttribArray(uvAttribIndex);
	glEnableVertexAttribArray(normalAttribIndex);

	//position attrib:
	glVertexAttribFormat(positionAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexAttribBinding(positionAttribIndex, bufferBindIndex);

	//uvs attrib:
	glVertexAttribFormat(uvAttribIndex,2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uvs));
	glVertexAttribBinding(uvAttribIndex, bufferBindIndex);

	//normals attrib:
	glVertexAttribFormat(normalAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normals));
	glVertexAttribBinding(normalAttribIndex, bufferBindIndex);


	//shaders

	const char* vertexShaderStr = R"(#version 450
       
      layout(location = 0) in vec3 pos;
      layout(location = 1) in vec2 uvs;
      layout(location = 2) in vec3 normals; 
         
      layout(location = 0) uniform mat4 u_MVP;
 
      out smooth vec2 v_uvs;
      void main()
      {
         v_uvs = uvs;
         gl_Position = u_MVP * vec4(pos,1.0);
      }
 
          
   )";

	const char* fragShaderStr = R"(#version 450
       in smooth vec2 v_uvs;

       layout(binding = 0)uniform sampler2D colorMap;

       out vec4 PIXEL;
       void main()
       {
          PIXEL = texture(colorMap, v_uvs);
       }

   )";

	 

	auto texture =  graphicsAPI->LoadTexture("assets/lena_color_512.png",false);


	//....  upload to gpu 

    GLuint prog = graphicsAPI->CompileShaderProgram(vertexShaderStr, fragShaderStr);
	

	glm::mat4 proj = glm::perspectiveFov(glm::radians(50.0f), (float)WIN_W, (float)WIN_H, 0.1f, 5000.0f);

	SceneNode node1;

	node1.SetPosition(0.0f, 0.0f, -1000.0f);
	node1.SetRotation(0.0f, 45.0f, 0.0f);
	node1.SetScale(100.0f, 100.0f, 1.0f);

	node1.UpdateTransform(glm::mat4(1.0f));

	
	//glBindTexture(GL_TEXTURE_2D, texture.handle);
	//Here is the start of our naive render loop
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	while (!renderContext.OnWindowClosing())
	{
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//here we render...

		glUseProgram(prog);

		glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, texture.handle);
	
		glProgramUniformMatrix4fv(prog, 0, 1, GL_FALSE, &(proj * node1.GetWorldMatrix())[0][0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
 
		renderContext.SwapBuffers();
	}


	renderContext.Destroy();

	printf("Time total on exit %f seconds\n", timer.getElapsedTimeInSec() - tStart);
	return EXIT_SUCCESS;
}


