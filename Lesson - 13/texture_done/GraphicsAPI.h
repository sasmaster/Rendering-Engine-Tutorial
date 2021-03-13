#ifndef  SGE_GRAPHICS_API_H
#define  SGE_GRAPHICS_API_H

#include "Engine.h"

#include "glad/glad.h"
#include <stdint.h>
#include <vector>
namespace sge
{

	struct Texture
	{
		GLuint   handle  = 0; //GPU handle
		uint32_t width   = 0;
		uint32_t height  = 0;
	};

	class GraphicsAPI
	{

		SGE_DISABLE_COPY_ASSIGN(GraphicsAPI)

		std::vector<Texture*> mTextures;

		GraphicsAPI();

		bool Init();

		void ShutDown();

		GLuint CompileShader(const char* shaderStr,const GLenum shaderType);

	public:


		GLuint CompileShaderProgram(const char* vertStr,const char* fragStr);

		/**
		* The caller must deallocate buffer after used.
		*/
		Texture* LoadTexture(const char* path, const bool mipmaps);

		Texture* CreateTexture(const uint8_t* buffer, const uint32_t width, const uint32_t height,const bool mipmaps);
	
		~GraphicsAPI();

	 
		static bool Create();

		static void  Dispose();

	};

	
	extern GraphicsAPI* graphicsAPI;

}




#endif // ! SGE_GRAPHICS_API_H
