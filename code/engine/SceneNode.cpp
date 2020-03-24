#include "SceneNode.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <stdio.h>
#include <algorithm>
namespace sge
{

	SceneNode::SceneNode()
		:
		 mParent(nullptr)
		,mPosition(0.0f)
		,mRotation(0.0f)
		,mScale(1.0f)
		,mTransformDirty(true)
	{
	}

	void SceneNode::AddNode(SceneNode* childNode)
	{
		if (this == childNode)
		{
			return;
		}

		if (std::find(mChildren.cbegin(),mChildren.cend(),childNode) == mChildren.end())
		{
			if (childNode->mParent)
			{
				childNode->mParent->RemoveNode(childNode);
			}

			childNode->mParent = this;
			mChildren.push_back(childNode);
		}


	}

	void SceneNode::RemoveNode(SceneNode* childNode)
	{
		mChildren.erase(std::remove(mChildren.begin(),mChildren.end(),childNode ),mChildren.end());
	}

	void SceneNode::SetName(const char* name)
	{
		snprintf(mName, sizeof(mName), "%s", name);
	}

	void SceneNode::SetPosition(float x, float y, float z)
	{
		mPosition = glm::vec3(x,y,z);
		mTransformDirty = true;
	}

	void SceneNode::SetRotation(float x, float y, float z)
	{
		mRotation = glm::vec3(x,y,z);
		mTransformDirty = true;
	}

	void SceneNode::SetScale(float x, float y, float z)
	{
		mScale = glm::vec3(x,y,z);
		mTransformDirty = true;
	}

	 
	void SceneNode::UpdateTransform(const glm::mat4& parent, bool dirtyFlag)
	{

		dirtyFlag |= mTransformDirty;

		if (dirtyFlag)
		{
			//printf("processing node %s  %i\n",mName);
			 
			//T>R>S
			glm::mat4 model = glm::translate(glm::mat4(1.0f), mPosition);

			model *= glm::mat4_cast(

				//Pitch,Yaw,Roll.
				//Y,P,R
				glm::angleAxis(glm::radians(mRotation.y), glm::vec3(0.0, 1.0f, 0.0f))    *  //y
				glm::angleAxis(glm::radians(mRotation.x), glm::vec3(1.0, 0.0f, 0.0f))    *  //x
				glm::angleAxis(glm::radians(mRotation.z), glm::vec3(0.0, 0.0f, 1.0f))       //z
			);

			model = glm::scale(model, mScale);

			mWorldMatrix = parent * model;
		}

		for (auto child: mChildren)
		{
			child->UpdateTransform(mWorldMatrix, dirtyFlag);
		}

		mTransformDirty = false;
	}

	SceneNode::~SceneNode()
	{
	}
}