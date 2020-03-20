#include "GraphicsAPI.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
namespace sge
{

	GraphicsAPI* graphicsAPI = nullptr;


	GraphicsAPI::GraphicsAPI()
	{
	}

	bool GraphicsAPI::Init()
	{

		//TODO
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
		//vert:
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
		GLint isCompiled = 0;
		glGetProgramiv(prog, GL_LINK_STATUS, &isCompiled);
		if (GL_FALSE == isCompiled)
		{
			GLint maxLength = 0;
			glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = (char*)malloc(maxLength);
			glGetProgramInfoLog(prog, maxLength, &maxLength, infoLog);

			printf("Program link error: %s\n", infoLog);
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


	Texture GraphicsAPI::LoadTexture(const char* path, const bool mipmaps)
	{
		int comp = 0;
		int w = 0;
		int h = 0;

		stbi_set_flip_vertically_on_load(1);
	    uint8_t* buff =	stbi_load(path, &w, &h, &comp, STBI_rgb_alpha);
		SGE_ASSERT(buff);

		Texture tex = CreateTexture(buff,w,h, mipmaps);

		stbi_image_free(buff);

		return tex;
	}

	Texture GraphicsAPI::CreateTexture(const uint8_t* buffer,const uint32_t width,const uint32_t height,const bool mipmaps)
	{
		 
		Texture tex;
		tex.width = width;
		tex.height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &tex.handle);
	 
		GLsizei numMipmaps = 1;
		GLint minFilter = GL_LINEAR;

		if (mipmaps)
		{
			
			numMipmaps = 1 + static_cast<GLsizei>(floor(log2(glm::max(width,height))));
			minFilter = GL_LINEAR_MIPMAP_LINEAR; //trilinar
		}


		glTextureStorage2D(tex.handle, numMipmaps, GL_RGBA8, width, height);

		glTextureSubImage2D(tex.handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		glTextureParameteri(tex.handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(tex.handle, GL_TEXTURE_MIN_FILTER, minFilter);

		glTextureParameteri(tex.handle, GL_TEXTURE_BASE_LEVEL, 0);

		glTextureParameteri(tex.handle, GL_TEXTURE_MAX_LEVEL, numMipmaps - 1);

		if (mipmaps)
		{
			glGenerateTextureMipmap(tex.handle);
		}


		return tex;
	}

	GraphicsAPI::~GraphicsAPI()
	{
	}

}