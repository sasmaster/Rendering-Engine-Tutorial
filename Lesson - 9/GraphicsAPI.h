#ifndef  SGE_GRAPHICS_API_H
#define  SGE_GRAPHICS_API_H

#include "Engine.h"

#include "glad/glad.h"
#include <stdint.h>
namespace sge
{

	struct Texture
	{
		uint32_t handle  = 0; //GPU handle
		uint32_t width   = 0;
		uint32_t height  = 0;
	};

	class GraphicsAPI
	{

		SGE_DISABLE_COPY_ASSIGN(GraphicsAPI)

		GraphicsAPI();

		bool Init();

		GLuint CompileShader(const char* shaderStr,const GLenum shaderType);

	public:


		GLuint CompileShaderProgram(const char* vertStr,const char* fragStr);

		/**
		* The caller must deallocate buffer after used.
		*/
		Texture LoadTexture(const char* path);

		Texture CreateTexture(const uint8_t* buffer, const uint32_t width, const uint32_t height);
	
		~GraphicsAPI();

	 
		static bool Create();

	};

	
	extern GraphicsAPI* graphicsAPI;

}




#endif // ! SGE_GRAPHICS_API_H
