/*
**	Author:		Martin Schwarz
**	Name:		ICamera.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_ICAMERA_H
#define MGF_ICAMERA_H

#include "../Include.h"

namespace mgf{

class ICamera{
public:
	virtual ~ICamera(){};

	virtual void setup(float fov, float screenratio, float far, float near) = 0;
	virtual void setScreenratio(float screenratio) = 0;

	virtual void update(glm::vec3 pos, glm::vec2 rot) = 0;

    virtual void setPos(glm::vec3 pos) = 0;
    virtual void setRot(glm::vec3 rot) = 0;

    virtual glm::vec3 getPos() = 0;
    virtual glm::vec3 getRot() = 0;

	virtual glm::mat4 getVP() = 0;
	virtual glm::mat4 getV() = 0;
	virtual glm::mat4 getP() = 0;
};

} // mgf

#endif // MGF_ICAMERA_H
