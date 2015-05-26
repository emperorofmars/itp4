/*
**	Author:		Martin Schwarz
**	Name:		Material.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Material.h"

namespace mgf{

Material::Material(){
	mDiffuseColor = glm::vec4(0.8, 0.4, 0.2, 1);
	mEmissiveColor = glm::vec4(0, 0, 0, 1);
	mAmbientColor = glm::vec4(0.05, 0.05, 0.05, 1);
	mDiffuseColor = glm::vec4(0.8, 0.4, 0.2, 1);
	mSpecularColor = glm::vec4(0.5, 0.5, 0.5, 1);
	mShininess = 25;
	mShadingType = 1;
}

Material::~Material(){
}

} // mgf
















