#include "TextureMaterial.h"


namespace sge
{
	TextureMaterial::TextureMaterial()
		:
		mDiffuseMap(nullptr)
	{

	}

	void TextureMaterial::SetDiffuseMap(Texture* texture)
	{
		mDiffuseMap = texture;
	}

	TextureMaterial::~TextureMaterial()
	{

	}

}