/*
**	Author:		Martin Schwarz
**	Name:		Light.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Light.h"

namespace mgf{

Light::Light(){
	mType = 1;
	mStrengthDiffuse = 1;
	mStrengthSpecular = 1;
	mActive = 1;
	mColor = glm::vec3(1.f, 1.f, 1.f);
	mPosition = glm::vec3(0.f, 0.f, 0.f);
	mDirection = glm::vec3(0.f, -1.f, 0.f);
}

Light::~Light(){
}

} // mgf
















