#ifndef SGE_GEOMETRY_H
#define SGE_GEOMETRY_H

#include "glad/glad.h"
#include "glm/glm.hpp"
namespace sge
{

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uvs;
		glm::vec3 normals;
	};

	class Geometry
	{

	
		GLuint vertexBufferObject; //VBO
		


	public:

		GLuint    vertexArrayObject;  //VAO
		uint32_t  mNumVertices;
		GLenum    mDrawType;

		Geometry();

		void Create(GLenum drawType,const Vertex* vertices, const uint32_t numVertices);

		void Destroy();

		~Geometry();

	 

	};

	
}

#endif // !SGE_GEOMETRY_H
