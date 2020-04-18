#ifndef SGE_SCENE_NODE_H
#define SGE_SCENE_NODE_H

#include "Engine.h"
#include "glm/glm.hpp"

#include <vector>

namespace sge
{
	enum class NodeType :uint8_t
	{
		TRANSFORM_NODE,
		MESH_NODE
	};

	class Scene;
	class SceneNode
	{
		Scene*                  mScene;
		SceneNode*              mParent;

		friend class Scene;

		std::vector<SceneNode*> mChildren;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		glm::mat4 mWorldMatrix;
		bool      mTransformDirty;
		char      mName[64];


		

	protected:

		SceneNode();
		~SceneNode();
		NodeType mNodeType;

	public:

		SGE_DISABLE_COPY_ASSIGN(SceneNode)

	

		void AddNode(SceneNode* childNode);

		void RemoveNode(SceneNode* childNode);

		void SetName(const char* name);

		void SetPosition(float x,float y,float z);

		void SetRotation(float x, float y, float z);

		void SetScale(float x, float y, float z);

		NodeType GetNodeType()const
		{
			return mNodeType;
		}

		const std::vector<SceneNode*>& GetChildren()const
		{
			return mChildren;
		}

		const glm::mat4& GetWorldMatrix()const
		{
			return mWorldMatrix;
		}

	


		void UpdateTransform(const glm::mat4& parent,bool dirtyFlag);

	

 

	};

	

}

#endif