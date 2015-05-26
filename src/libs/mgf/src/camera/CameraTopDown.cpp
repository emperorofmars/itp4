/*
**	Author:		Martin Schwarz
**	Name:		CameraTopDown.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "CameraTopDown.h"

namespace mgf{

CameraTopDown::CameraTopDown(float fov, float screenratio, float far, float near)
    : BaseCamera(fov, screenratio, far, near)
{
	mPos = glm::vec3(0, 10, 0);
	mRot = glm::vec3(0, 0, 0);
	mDir = glm::normalize(glm::vec3(0, -1.5, -1));
	mUp = glm::vec3(0, 1, 0);
	mRight = glm::vec3(1, 0, 0);
	mView = glm::lookAt(mPos, mPos + mDir, mUp);
}

CameraTopDown::~CameraTopDown(){
}

void CameraTopDown::update(glm::vec3 pos, glm::vec2 rot){

	mPos += glm::vec3(1.f, 0.f, 0.f) * pos[0];
	mPos += glm::vec3(0.f, 1.f, 0.f) * pos[1];
	mPos += glm::vec3(0.f, 0.f, -1.f) * pos[2];

	mView = glm::lookAt(mPos, mPos + mDir, mUp);

	return;
}

} // mgf












