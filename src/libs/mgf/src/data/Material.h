/*
**	Author:		Martin Schwarz
**	Name:		Material.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_MATERIAL_H
#define MGF_MATERIAL_H

#include "../Include.h"
#include "Texture.h"

namespace mgf{

class Material{
public:
	Material();
	~Material();

	std::string mName;

	std::vector<std::shared_ptr<Texture>> mDiffuseTextures;
	glm::vec4 mEmissiveColor;
	glm::vec4 mAmbientColor;
	glm::vec4 mDiffuseColor;
	glm::vec4 mSpecularColor;
	float mShininess;
	int mShadingType;
};

} // mgf

#endif // MGF_MATERIAL_H








