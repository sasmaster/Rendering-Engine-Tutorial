#include "SceneNode.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

namespace sge
{

	SceneNode::SceneNode()
		:mPosition(0.0f)
		,mRotation(0.0f)
		,mScale(1.0f)
	{
	}

	void SceneNode::SetPosition(float x, float y, float z)
	{
		mPosition = glm::vec3(x,y,z);
	}

	void SceneNode::SetRotation(float x, float y, float z)
	{
		mRotation = glm::vec3(x,y,z);
	}

	void SceneNode::SetScale(float x, float y, float z)
	{
		mScale = glm::vec3(x,y,z);
	}


	void SceneNode::UpdateTransform(const glm::mat4& parent)
	{
		//T>R>S
		glm::mat4 model = glm::translate(glm::mat4(1.0f),mPosition);

		model *= glm::mat4_cast(

			//Pitch,Yaw,Roll.
			//Y,P,R
			glm::angleAxis(glm::radians(mRotation.y), glm::vec3(0.0, 1.0f, 0.0f))    *  //y
			glm::angleAxis(glm::radians(mRotation.x), glm::vec3(1.0, 0.0f, 0.0f))    *  //x
			glm::angleAxis(glm::radians(mRotation.z), glm::vec3(0.0, 0.0f, 1.0f))       //z
		);

		model = glm::scale(model,mScale);

		mWorldMatrix = parent * model;

	}

	SceneNode::~SceneNode()
	{
	}
}