#ifndef SGE_SCENE_NODE_H
#define SGE_SCENE_NODE_H


#include "glm/glm.hpp"

namespace sge
{
	class SceneNode
	{

		glm::vec3 mPosition;
		glm::vec3 mRotation;
		glm::vec3 mScale;

		glm::mat4 mWorldMatrix;


	public:

		SceneNode();

		void SetPosition(float x,float y,float z);

		void SetRotation(float x, float y, float z);

		void SetScale(float x, float y, float z);


		const glm::mat4& GetWorldMatrix()const
		{
			return mWorldMatrix;
		}


		void UpdateTransform(const glm::mat4& parent);

		~SceneNode();

 

	};

	

}

#endif