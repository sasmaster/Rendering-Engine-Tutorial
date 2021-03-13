#include "CameraNode.h"
#include "glm/gtc/matrix_transform.hpp"
namespace sge
{
	CameraNode::CameraNode()
	{
	}

	void CameraNode::Init(float fov, float w, float h, float nearPlane, float farPlane)
	{
		mProjection =
			glm::perspectiveFov(glm::radians(fov), w, h, nearPlane, farPlane);
	}

	glm::mat4 CameraNode::GetView()const 
	{
		return glm::inverse(this->GetWorldMatrix());
	}

	CameraNode::~CameraNode()
	{
	}
}