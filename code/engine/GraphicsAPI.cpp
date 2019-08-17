
#include "GraphicsAPI.h"


namespace sge
{
	GraphicsAPI* graphicsAPI = nullptr;

	GraphicsAPI::GraphicsAPI()
	{
	}

	bool GraphicsAPI::Init()
	{
		return true;
	}

	bool GraphicsAPI::Create()
	{
		if (!graphicsAPI)
		{
			graphicsAPI = newnothrow GraphicsAPI;
			SGE_ASSERT(graphicsAPI);
			return graphicsAPI->Init();
		}
		printf("GraphicsAPI instance already exists\n");
		return false;
	}


	GLuint GraphicsAPI::CompileShader(const char* shaderStr, const GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		glShaderSource(shader, 1, &shaderStr, NULL);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = (char*)malloc(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

			printf("Shader compilation error: %s\n", infoLog);
			free(infoLog);
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	GLuint GraphicsAPI::CompileShaderProgram(const char* vertStr, const char* fragStr)
	{

		const GLuint prog = glCreateProgram();
		const GLuint vertShader = CompileShader(vertStr, GL_VERTEX_SHADER);
		const GLuint fragShader = CompileShader(fragStr, GL_FRAGMENT_SHADER);
		glAttachShader(prog, vertShader);
		glAttachShader(prog, fragShader);
		glLinkProgram(prog);
		//link errors and validation checks...
		GLint isLinked = 0;
		glGetProgramiv(prog, GL_LINK_STATUS, &isLinked);
		if (GL_FALSE == isLinked)
		{
			GLint maxLength = 0;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = (char*)malloc(maxLength);
			glGetProgramInfoLog(prog, maxLength, &maxLength, infoLog);

			printf("Shader program linking error: %s\n", infoLog);
			free(infoLog);
			glDeleteProgram(prog);
			return 0;
		}

		glDetachShader(prog, vertShader);
		glDetachShader(prog, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		return prog;
	}
}