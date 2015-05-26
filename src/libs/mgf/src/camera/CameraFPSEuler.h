/*
**	Author:		Martin Schwarz
**	Name:		CameraFPSEuler.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_FPSEULER_CAMERA_H
#define MGF_FPSEULER_CAMERA_H

#include "../Include.h"
#include "BaseCamera.h"

namespace mgf{

class CameraFPSEuler : public BaseCamera{
public:
    CameraFPSEuler(float fov = 90.f, float screenratio = 1.f, float far = 1000.f, float near = 0.1f);
	virtual ~CameraFPSEuler();

	virtual void update(glm::vec3 pos, glm::vec2 rot);
};

} // mgf

#endif // MGF_FPSEULER_CAMERA_H
