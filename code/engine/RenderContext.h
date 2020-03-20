#ifndef SGE_RENDER_CONTEXT_H
#define SGE_RENDER_CONTEXT_H

#include <stdint.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
 
namespace sge {

	class RenderContext
	{

		GLFWwindow* mWindow;
		uint32_t mWidth;
		uint32_t mHeight;
		bool mDebugContext;

	public:
		explicit RenderContext(uint32_t width, uint32_t height,bool debugContext);
		~RenderContext();


		bool Create();

		void Destroy();

		inline void SwapBuffers()
		{
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}

		inline bool OnWindowClosing()
		{
			return glfwWindowShouldClose(mWindow) != 0;
		}

	private:

	};

}




#endif // !SGE_RENDER_CONTEXT_H
