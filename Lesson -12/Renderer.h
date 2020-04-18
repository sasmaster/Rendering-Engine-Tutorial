#ifndef SGE_RENDERER_H
#define SGE_RENDERER_H
#include "Engine.h"

#include "GraphicsAPI.h"

namespace sge
{
	class Scene;
	class Renderer
	{

		GLuint prog;

	public:

		SGE_DISABLE_COPY_ASSIGN(Renderer)

		Renderer();

		void Render(const Scene* scene);

		void SetBackgroundColor(float r, float g, float b, float a);

		~Renderer();

	 

	};

	
}



#endif // !SGE_RENDERER_H
