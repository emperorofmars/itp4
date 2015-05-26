/*
**	Author:		Martin Schwarz
**	Name:		CameraFlightQuat.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_FLIGHTQUAT_CAMERA_H
#define MGF_FLIGHTQUAT_CAMERA_H

#include "../Include.h"
#include "BaseCamera.h"

namespace mgf{

class CameraFlightQuat : public BaseCamera{
public:
    CameraFlightQuat(float fov = 90.f, float screenratio = 1.f, float far = 1000.f, float near = 0.1f);
	virtual ~CameraFlightQuat();

	virtual void update(glm::vec3 pos, glm::vec3 rot);
};

} // mgf

#endif // MGF_FLIGHTQUAT_CAMERA_H
