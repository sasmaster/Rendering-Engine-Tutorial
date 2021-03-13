// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"

#include "Timer.h"

#include "RenderContext.h"

#include "glm/glm.hpp"


#include "GraphicsAPI.h"
#include "SceneNode.h"
#include "Geometry.h"
#include "Scene.h"
#include "MeshNode.h"
#include "CameraNode.h"
#include "Renderer.h"



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

	Scene  mainScene;
	Renderer renderer;



	const uint32_t numVertices = 4;
	Vertex vertices[numVertices] = {
	
		{glm::vec3(0.5f,0.5f,0.0f)  ,glm::vec2(1.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,0.5f,0.0f) ,glm::vec2(0.0f,1.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(-0.5f,-0.5f,0.0f),glm::vec2(0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)},
		{glm::vec3(0.5f,-0.5f,0.0f) ,glm::vec2(1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)}
	
	};

	Geometry geom;

	geom.Create(GL_TRIANGLE_FAN,vertices, numVertices);

	MeshNode*  meshNode1 = mainScene.CreateSceneNode<MeshNode>();
	meshNode1->SetGeometry(&geom);
	

	

	 

	auto texture =  graphicsAPI->LoadTexture("assets/lena_color_512.png",false);


	//....  upload to gpu 

  
	

	CameraNode* camera = mainScene.CreateSceneNode<CameraNode>();
	camera->Init(54.0f, WIN_W, WIN_H, 0.1f, 5000.0f);

	//camera->SetPosition(200.0f, 0.0f, 0.0f);
	 
	mainScene.AddNode(camera);
	mainScene.SetCurrentCamera(camera);

 
	meshNode1->SetName("mesh A");
	meshNode1->SetPosition(0.0f, 0.0f, -1000.0f);
	meshNode1->SetRotation(0.0f, 45.0f, 0.0f);
	meshNode1->SetScale(100.0f, 100.0f, 1.0f);

	mainScene.AddNode(meshNode1);

	
	
	//glBindTexture(GL_TEXTURE_2D, texture.handle);
	//Here is the start of our naive render loop


	
	float rotY = 0.0f;
	while (!renderContext.OnWindowClosing())
	{

		/////////////////  Engine logic /game logic  //////////////////////

		meshNode1->SetRotation(0.0f, rotY, 0.0f);
		rotY += 1.5f;
		///////////////////// Run scene update ////////////////////////

		mainScene.Update();
		renderer.Render(&mainScene);

	    ////////////////  Rendering part ////////////////////
		
 
		renderContext.SwapBuffers();
	}

	GraphicsAPI::Dispose();
	renderContext.Destroy(); 
	//----------- GL context id DEAD -----------------
 
	

	printf("Time total on exit %f seconds\n", timer.getElapsedTimeInSec() - tStart);
	return EXIT_SUCCESS;
}


