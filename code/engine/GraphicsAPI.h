#ifndef SGE_GRAPHICS_API
#define SGE_GRAPHICS_API

#include "Engine.h"
#include "glad/glad.h"

namespace sge
{


	class GraphicsAPI
	{

		SGE_DISABLE_COPY_ASSIGN(GraphicsAPI)

		GraphicsAPI();
		
		bool Init();

		GLuint CompileShader(const char* shaderStr, const GLenum shaderType);


	public:

		GLuint CompileShaderProgram(const char* vertStr, const char* fragStr);


		~GraphicsAPI()
		{
		}

		static bool Create();

	};


	extern GraphicsAPI* graphicsAPI;


}

#endif // !SGE_GRAPHICS_API
