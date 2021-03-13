#pragma once
#ifndef SGE_TEXTURE_MATERIAL_H
#define SGE_TEXTURE_MATERIAL_H

#include "IMaterial.h"
namespace sge
{
	struct Texture;
	class TextureMaterial final :public IMaterial
	{
		
		Texture* mDiffuseMap;

	public:

		TextureMaterial();

		void SetDiffuseMap(Texture* texture);

		const Texture* GetDiffuseMap()const
		{
			return mDiffuseMap;
		}

		~TextureMaterial()override final;
	};

}


#endif // !SGE_IMATERIAL_H
