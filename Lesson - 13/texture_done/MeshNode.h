#ifndef SGE_MESH_NODE_H
#define SGE_MESH_NODE_H

#include "SceneNode.h"

namespace sge
{
	class Geometry;
	class IMaterial;
	class MeshNode final: public SceneNode
	{
		friend class Scene;

		Geometry* mGeometry;
		IMaterial* mMaterial;

		MeshNode();
		~MeshNode();



	public:
		SGE_DISABLE_COPY_ASSIGN(MeshNode)
		
		MeshNode(Geometry* geometry);

		void SetGeometry(Geometry* geometry);

		const Geometry* GetGeometry()const
		{
			return mGeometry;
		}

		void SetMaterial(IMaterial* material)
		{
			mMaterial = material;
		}

		IMaterial* GetMaterial()
		{
			return mMaterial;
		}



	};




}


#endif // !SGE_MESH_NODE_H
