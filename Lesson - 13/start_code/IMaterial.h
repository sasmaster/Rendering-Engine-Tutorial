#pragma once
#ifndef SGE_IMATERIAL_H
#define SGE_IMATERIAL_H

#include "glm/glm.hpp"
namespace sge
{
	class IMaterial
	{
		
	protected:

		glm::vec4 mDiffuseColor;

	public:

		IMaterial()
		{
		}

		void SetDiffuseColor(const glm::vec4& color)
		{
			SetDiffuseColor(color.r, color.g, color.b, color.a);
		}

		void SetDiffuseColor(const float r,const float g,const float b,const float a)
		{
			mDiffuseColor.r = r;
			mDiffuseColor.g = g;
			mDiffuseColor.b = b;
			mDiffuseColor.a = a;
		}


		const glm::vec4& GetDiffuseColor()const
		{
			return mDiffuseColor;
		}
		

		virtual ~IMaterial()
		{
		}

	 

	};

}


#endif // !SGE_IMATERIAL_H
