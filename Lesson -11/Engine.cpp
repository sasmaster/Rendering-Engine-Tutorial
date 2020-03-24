// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"

#include "Timer.h"

#include "RenderContext.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GraphicsAPI.h"
#include "SceneNode.h"
#include "Geometry.h"



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
	Vertex vertices[numVertices] = {
	
		{glm::vec3(0.5f,0.5f,0.0f)  ,glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,0.5f,0.0f) ,glm::vec2(0.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,-0.5f,0.0f) ,glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)}
	
	};

	Geometry geom;

	geom.Create(GL_TRIANGLE_FAN,vertices, numVertices);


	

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

	SceneNode rootNode; // root node
	rootNode.SetName("Root node");

	rootNode.SetPosition(0.0f, 0.0f, -1000.0f);
	rootNode.SetRotation(0.0f, 45.0f, 0.0f);
	rootNode.SetScale(100.0f, 100.0f, 1.0f);

	SceneNode node1; // root node
	node1.SetName("node A");
	SceneNode node2; // root node
	node2.SetName("node B");
	SceneNode node3; // root node
	node3.SetName("node C");
	SceneNode node4; // root node
	node4.SetName("node D");

	rootNode.AddNode(&node1);
	rootNode.AddNode(&node2);
	node1.AddNode(&node3);
	node2.AddNode(&node4);


	rootNode.UpdateTransform(glm::mat4(1.0f),false);

	rootNode.UpdateTransform(glm::mat4(1.0f), false);


	node2.RemoveNode(&node4);


	rootNode.UpdateTransform(glm::mat4(1.0f), true);




	
	//glBindTexture(GL_TEXTURE_2D, texture.handle);
	//Here is the start of our naive render loop
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	glBindVertexArray(geom.vertexArrayObject);

	while (!renderContext.OnWindowClosing())
	{
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//here we render...


		glUseProgram(prog);

		glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, texture.handle);
	
		glProgramUniformMatrix4fv(prog, 0, 1, GL_FALSE, &(proj * node1.GetWorldMatrix())[0][0]);

		glDrawArrays(GL_TRIANGLE_FAN, 0, geom.mNumVertices);
 
		renderContext.SwapBuffers();
	}


	renderContext.Destroy();

	printf("Time total on exit %f seconds\n", timer.getElapsedTimeInSec() - tStart);
	return EXIT_SUCCESS;
}


