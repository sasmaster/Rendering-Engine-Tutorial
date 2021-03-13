#include "Renderer.h"
#include "Scene.h"
#include "MeshNode.h"
#include "CameraNode.h"
#include "Geometry.h"

namespace sge
{

	Renderer::Renderer()
	{

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
          PIXEL = glm::vec4(1.0);// texture(colorMap, v_uvs);
       }

   )";

		prog = graphicsAPI->CompileShaderProgram(vertexShaderStr, fragShaderStr);
	}

	void Renderer::SetBackgroundColor(float r, float g, float b, float a)
	{
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}

	void Renderer::Render(const Scene* scene)
	{
		const auto& renderables = scene->GetRenderableNodes();
		const size_t numrenderables = renderables.size();
		const auto currentCamera = scene->GetCurrentCamera();
		assert(currentCamera);
		for (size_t i = 0; i < numrenderables; i++)
		{
			const auto renderNode = renderables[i];

			const auto geom = renderNode->GetGeometry();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//here we render...
			glBindVertexArray(geom->vertexArrayObject);

			glUseProgram(prog);

			//glBindMultiTextureEXT(GL_TEXTURE0, GL_TEXTURE_2D, texture.handle);

			glProgramUniformMatrix4fv(prog, 0, 1, GL_FALSE,
				&(currentCamera->GetProjection() * currentCamera->GetView() * renderNode->GetWorldMatrix())[0][0]);

			glDrawArrays(geom->mDrawType, 0, geom->mNumVertices);

		}

	}

	Renderer::~Renderer()
	{
	}

}