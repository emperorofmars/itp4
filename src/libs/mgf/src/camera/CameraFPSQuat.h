/*
**	Author:		Martin Schwarz
**	Name:		CameraFPSQuat.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_FPSQUAT_CAMERA_H
#define MGF_FPSQUAT_CAMERA_H

#include "../Include.h"
#include "BaseCamera.h"

namespace mgf{

class CameraFPSQuat : public BaseCamera{
public:
    CameraFPSQuat(float fov = 90.f, float screenratio = 1.f, float far = 1000.f, float near = 0.1f);
	virtual ~CameraFPSQuat();

	virtual void update(glm::vec3 pos, glm::vec2 rot);
};

} // mgf

#endif // MGF_FPSQUAT_CAMERA_H
