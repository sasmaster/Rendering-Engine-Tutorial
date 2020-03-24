#ifndef SGE_SCENE_NODE_H
#define SGE_SCENE_NODE_H


#include "glm/glm.hpp"

#include <vector>

namespace sge
{
	class SceneNode
	{

		SceneNode*              mParent;
		std::vector<SceneNode*> mChildren;
		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		glm::mat4 mWorldMatrix;
		bool      mTransformDirty;
		char mName[64];

	public:

		SceneNode();

		void AddNode(SceneNode* childNode);

		void RemoveNode(SceneNode* childNode);

		void SetName(const char* name);

		void SetPosition(float x,float y,float z);

		void SetRotation(float x, float y, float z);

		void SetScale(float x, float y, float z);


		const glm::mat4& GetWorldMatrix()const
		{
			return mWorldMatrix;
		}


		void UpdateTransform(const glm::mat4& parent,bool dirtyFlag);

		~SceneNode();

 

	};

	

}

#endif