/*
**	Author:		Martin Schwarz
**	Name:		Positionable.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Positionable.h"

#include "../helper/Helper.h"

namespace mgf{

Positionable::Positionable(){
	mTRS = glm::mat4(1);
	mScale = glm::vec3(1.f, 1.f, 1.f);
}

Positionable::~Positionable(){
}

void Positionable::translate(glm::vec3 data){
	mTranslation += data;
}

void Positionable::rotate(float angle, glm::vec3 data){
	mTRS = glm::rotate(glm::mat4(1), angle, data) * mTRS;
}

void Positionable::scale(glm::vec3 data){
	mScale *= data;
	mTRS *= glm::scale(glm::mat4(1), mScale);
}

void Positionable::setTranslation(glm::vec3 data){
	mTranslation = data;
}

void Positionable::setRotation(glm::mat4 data){
	mTRS = data;
	mTRS = glm::scale(glm::mat4(1), mScale) * mTRS;
}

void Positionable::setScale(glm::vec3 data){
	glm::vec3 diff(data / mScale);
	mScale = data;
	mTRS = glm::scale(glm::mat4(1), diff) * mTRS;
}

void Positionable::setTRS(glm::mat4 data){
	mTRS = data;
	mScale = glm::vec3(1.f, 1.f, 1.f);
	mTranslation = glm::vec3(mTRS[3]);
	mTRS[3][0] = 0; mTRS[3][1] = 0; mTRS[3][2] = 0;
}

glm::vec3 Positionable::getTranslation(){
	return mTranslation;
}

glm::mat4 Positionable::getRotation(){
	return mTRS;
}

glm::vec3 Positionable::getScale(){
	return mScale;
}

glm::mat4 Positionable::getTRS(){
	return glm::translate(glm::mat4(1), mTranslation) * mTRS;
}

} // mgf



















