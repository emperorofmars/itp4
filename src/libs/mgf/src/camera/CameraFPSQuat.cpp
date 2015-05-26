/*
**	Author:		Martin Schwarz
**	Name:		CameraFPSQuat.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "CameraFPSQuat.h"

namespace mgf{

CameraFPSQuat::CameraFPSQuat(float fov, float screenratio, float far, float near)
    : BaseCamera(fov, screenratio, far, near){}

CameraFPSQuat::~CameraFPSQuat(){
}

void CameraFPSQuat::update(glm::vec3 pos, glm::vec2 rot){
    mRot[0] = (float)rot[0] * -0.008f;
    mRot[1] = (float)rot[1] * -0.008f;

    mRight = glm::cross(mDir, mUp);
    glm::quat pitch = glm::angleAxis(mRot[1], mRight);
    pitch = glm::normalize(pitch);

    glm::quat heading = glm::angleAxis(mRot[0], glm::vec3(0, 1, 0));
    heading = glm::normalize(heading);

    glm::quat temp = glm::cross(pitch, heading);
    temp = glm::normalize(temp);

    glm::mat3 dirmat = glm::mat3_cast(temp);
    mDir = dirmat * mDir;
    mDir = glm::normalize(mDir);

    mRight = dirmat * mRight;
    mRight[1] = 0.f;
    mRight = glm::normalize(mRight);

    mUp = glm::cross(mRight, mDir);
    mUp = glm::normalize(mUp);

	mPos += mDir * pos[2];
	mPos += mRight * pos[0];

	mView = glm::lookAt(mPos, mPos + mDir, mUp);

	return;
}

} // mgf












