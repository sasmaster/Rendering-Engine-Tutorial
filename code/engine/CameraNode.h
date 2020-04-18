#ifndef SGE_CAMERA_NODE_H
#define SGE_CAMERA_NODE_H

#include "SceneNode.h"
#include "glm/glm.hpp"
namespace sge
{
	class CameraNode: public SceneNode
	{
		friend class Scene;

		glm::mat4 mProjection;
		CameraNode();
		~CameraNode();

	public:
		
		void Init(float fov,float w,float h,float nearPlane,float farPlane);
	 
		const glm::mat4& GetProjection()const
		{
			return mProjection;
		}

		glm::mat4 GetView()const;
		 
	};

	
}

#endif // !SGE_CAMERA_NODE_H
