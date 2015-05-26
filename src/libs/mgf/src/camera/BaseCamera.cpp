/*
**	Author:		Martin Schwarz
**	Name:		BaseCamera.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "BaseCamera.h"

namespace mgf{

BaseCamera::BaseCamera(float fov, float screenratio, float far, float near){
	setup(fov, screenratio, far, near);
	mPos = glm::vec3(0, 0, 0);
	mRot = glm::vec3(0, 0, 0);
	mDir = glm::vec3(0, 0, -1);
	mUp = glm::vec3(0, 1, 0);
	mRight = glm::vec3(1, 0, 0);
	mView = glm::lookAt(mPos, mPos + mDir, mUp);
}

BaseCamera::~BaseCamera(){
}

void BaseCamera::setup(float fov, float screenratio, float far, float near){
	mProjection = glm::perspective(fov * (float)M_PI / 180, screenratio, near, far);
	mFov = fov * M_PI / 180;
	mScreenratio = screenratio;
	mNear = near;
	mFar = far;
	return;
}

void BaseCamera::setScreenratio(float screenratio){
	mProjection = glm::perspective(mFov, screenratio, mNear, mFar);
	mScreenratio = screenratio;
	return;
}

void BaseCamera::setPos(glm::vec3 pos){
    mPos = pos;
	mView = glm::lookAt(mPos, mPos + mDir, mUp);
    return;
}

void BaseCamera::setRot(glm::vec3 rot){
    mRot = rot;
    return;
}

glm::vec3 BaseCamera::getPos(){
	return mPos;
}

glm::vec3 BaseCamera::getRot(){
	return mRot;
}

glm::mat4 BaseCamera::getVP(){
	return mProjection * mView;
}

glm::mat4 BaseCamera::getV(){
	return mView;
}

glm::mat4 BaseCamera::getP(){
	return mProjection;
}


} // mgf












