/*
**	Author:		Martin Schwarz
**	Name:		Light.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_LIGHT_H
#define MGF_LIGHT_H

#include "../Include.h"

namespace mgf{

enum{
	POINT_LIGHT = 1,
	SUN_LIGHT = 2,
	SPOT_LIGHT = 3,
};

class Light{
public:
	Light();
	~Light();

	std::string mName;

	float mActive;
	float mType;
	float mStrengthDiffuse;
	float mStrengthSpecular;
	glm::vec3 mColor;
	glm::vec3 mPosition;
	glm::vec3 mDirection;
	float mConeAngle;
};

} // mgf

#endif // MGF_LIGHT_H








