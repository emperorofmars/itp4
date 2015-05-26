/*
**	Author:		Martin Schwarz
**	Name:		CameraTopDown.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_TOPDOWN_CAMERA_H
#define MGF_TOPDOWN_CAMERA_H

#include "../Include.h"
#include "BaseCamera.h"

namespace mgf{

class CameraTopDown : public BaseCamera{
public:
    CameraTopDown(float fov = 90.f, float screenratio = 1.f, float far = 1000.f, float near = 0.1f);
	virtual ~CameraTopDown();

	virtual void update(glm::vec3 pos, glm::vec2 rot);
};

} // mgf

#endif // MGF_TOPDOWN_CAMERA_H
