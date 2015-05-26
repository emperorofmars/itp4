/*
**	Author:		Martin Schwarz
**	Name:		BaseCamera.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_BASECAMERA_H
#define MGF_BASECAMERA_H

#include "../Include.h"
#include "ICamera.h"

namespace mgf{

class BaseCamera : public ICamera{
public:
    BaseCamera(float fov = 90.f, float screenratio = 1.f, float far = 1000.f, float near = 0.1f);
	virtual ~BaseCamera();

	virtual void setup(float fov, float screenratio, float near, float far);
	virtual void setScreenratio(float screenratio);

    virtual void setPos(glm::vec3 pos);
    virtual void setRot(glm::vec3 rot);

    virtual glm::vec3 getPos();
    virtual glm::vec3 getRot();

	virtual glm::mat4 getVP();
	virtual glm::mat4 getV();
	virtual glm::mat4 getP();

protected:
	glm::mat4 mProjection, mView;
	glm::vec3 mPos, mRot, mDir, mUp, mRight;
	float mFov, mScreenratio, mNear, mFar;
};

} // mgf

#endif // MGF_BASECAMERA_H
