#include "MeshNode.h"
#include "Geometry.h"


namespace sge {

	MeshNode::MeshNode()
		:SceneNode()
		,mGeometry(nullptr)
	{
		mNodeType = NodeType::MESH_NODE;
	}

	MeshNode::MeshNode(Geometry* geometry)	
		:SceneNode()
		,mGeometry(geometry)
	{
		mNodeType = NodeType::MESH_NODE;
	}

	void MeshNode::SetGeometry(Geometry* geometry)
	{
		assert(geometry);
		mGeometry = geometry;
	}

	 
	MeshNode::~MeshNode()
	{
	}

}