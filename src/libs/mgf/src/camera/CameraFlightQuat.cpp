/*
**	Author:		Martin Schwarz
**	Name:		CameraFlightQuat.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "CameraFlightQuat.h"

namespace mgf{

CameraFlightQuat::CameraFlightQuat(float fov, float screenratio, float far, float near)
    : BaseCamera(fov, screenratio, far, near){}

CameraFlightQuat::~CameraFlightQuat(){
}

void CameraFlightQuat::update(glm::vec3 pos, glm::vec3 rot){
	int x = rot[1];
	int y = rot[0];
	//int z = rot[2];

    mRot[0] = (float)x * -0.008f;
    mRot[1] = (float)y * -0.008f;

    mRight = glm::cross(mDir, mUp);
    glm::quat pitch = glm::angleAxis(mRot[1], mRight);
    pitch = glm::normalize(pitch);

    glm::quat heading = glm::angleAxis(mRot[0], mUp);
    heading = glm::normalize(heading);

    glm::quat temp = glm::cross(pitch, heading);
    temp = glm::normalize(temp);

    glm::mat3 dirmat = glm::mat3_cast(temp);
    mDir = dirmat * mDir;
    mDir = glm::normalize(mDir);

    mUp = dirmat * mUp;
    mUp = glm::normalize(mUp);

	mPos += mDir * pos[0];
	mPos += mRight * pos[1];

	mView = glm::lookAt(mPos, mPos + mDir, mUp);

	return;
}

} // mgf












