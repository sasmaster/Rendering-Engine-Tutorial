#include "Geometry.h"



namespace sge {


	
	const uint32_t bufferBindIndex = 0;
	const uint32_t positionAttribIndex = 0;
	const uint32_t uvAttribIndex = 1;
	const uint32_t normalAttribIndex = 2;


	Geometry::Geometry()
		: vertexArrayObject(0)
		,vertexBufferObject(0)
		, mNumVertices(0)
		, mDrawType(GL_TRIANGLES)
	{
	}

	void Geometry::Create(GLenum drawType,  const Vertex* vertices,const uint32_t numVertices)
	{
		mDrawType = drawType;
		mNumVertices = numVertices;

		glCreateVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);

		glCreateBuffers(1, &vertexBufferObject);
		glBindVertexBuffer(bufferBindIndex, vertexBufferObject, 0, sizeof(Vertex));
		glNamedBufferStorage(vertexBufferObject, numVertices * sizeof(Vertex), vertices, GL_MAP_WRITE_BIT);
		
		 
		glEnableVertexAttribArray(positionAttribIndex);
		glEnableVertexAttribArray(uvAttribIndex);
		glEnableVertexAttribArray(normalAttribIndex);

		//position attrib:
		glVertexAttribFormat(positionAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
		glVertexAttribBinding(positionAttribIndex, bufferBindIndex);

		//uvs attrib:
		glVertexAttribFormat(uvAttribIndex, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uvs));
		glVertexAttribBinding(uvAttribIndex, bufferBindIndex);

		//normals attrib:
		glVertexAttribFormat(normalAttribIndex, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normals));
		glVertexAttribBinding(normalAttribIndex, bufferBindIndex);
		
		glBindVertexArray(0);

	}

	void Geometry::Destroy()
	{

	}

	Geometry::~Geometry()
	{
	}
}