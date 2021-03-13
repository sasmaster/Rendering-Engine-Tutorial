#include "RenderContext.h"




#include <stdio.h>
#include <assert.h>

namespace sge {



	static void ErrorCallback(int error, const char* message)
	{
		fprintf(stderr, "Error: %s\n", message);
	}


	static void GLDebugOutputCallback(GLenum source, GLuint type, GLenum id, GLenum severity, GLsizei length, const char* message, const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}


	RenderContext::RenderContext(uint32_t width,uint32_t height,bool debugContext)
		:
		 mWindow(nullptr)
		,mWidth(width)
		,mHeight(height)		
		,mDebugContext(debugContext)
	{

	}

	bool RenderContext::Create()
	{

		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
		{
			printf("Failed to init GLFW\n");
			return false;
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

		if (mDebugContext)
		{
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		}
	
 

		glfwWindowHint(GLFW_SAMPLES, 8);//MSAA

		assert(mWidth > 0 && mHeight > 0);
		mWindow = glfwCreateWindow(mWidth, mHeight, "Simple Engine", nullptr, nullptr);
		assert(mWindow);

		glfwMakeContextCurrent(mWindow);



		//GL API init
		if (!gladLoadGL())
		{
			this->Destroy();
			printf("Failed to load GL API\n");
			return false;
		}


		///////////  Calling OpenGL API is fine from here
 

		if (mDebugContext)
		{
			// GL debug ouput ...
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(GLDebugOutputCallback, nullptr);
		}


		return true;

	}

	void RenderContext::Destroy()
	{
		if (mWindow)
		{
			//start termination
			glfwDestroyWindow(mWindow);
			glfwTerminate();
			mWindow = nullptr;
		}
		
	}

	RenderContext::~RenderContext()
	{
	}

}
