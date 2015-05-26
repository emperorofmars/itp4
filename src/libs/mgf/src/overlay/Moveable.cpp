/*
**	Author:		Martin Schwarz
**	Name:		Moveable.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Moveable.h"

namespace mgf{

Moveable::Moveable(const std::string &name){
	mBase.reset(new OverlayNode("Base"));
	std::shared_ptr<Mesh> plane(createPlane());
	plane->mMaterial->mEmissiveColor = glm::vec4(0.5, 0.5, 0.5, 1);
	plane->mMaterial->mShadingType = 0;
	mBase->addMesh(plane);
	this->scale(glm::vec2(0.1f, 0.1f));
}

Moveable::~Moveable(){

}

bool Moveable::render(std::shared_ptr<Renderer> renderer){
	if(mBase)
		return mBase->render(renderer);
	else return false;
}

bool Moveable::setName(const std::string &name){
	return false;
}

void Moveable::translate(glm::vec2 pos){
	if(mBase)
		mBase->translate(glm::vec3(pos[0], -pos[1], 0));
	return;
}

void Moveable::setPos(glm::vec2 pos){
	if(mBase)
		mBase->setTranslation(glm::vec3(pos[0], -pos[1], mBase->getTranslation()[2]));
	return;
}

void Moveable::setLayer(int layer){
	if(mBase)
		mBase->setTranslation(glm::vec3(mBase->getTranslation()[0], mBase->getTranslation()[1], layer));
	return;
}

void Moveable::scale(glm::vec2 scale){
	if(mBase)
		mBase->scale(glm::vec3(scale, 1));
	return;
}

void Moveable::setScale(glm::vec2 scale){
	if(mBase)
		mBase->setScale(glm::vec3(scale, 1));
	return;
}

std::string Moveable::getName(){
	if(mBase)
		return mBase->getName();
	else return "";
}

glm::vec2 Moveable::getPos(){
	if(mBase)
		return glm::vec2(mBase->getTranslation());
	else return glm::vec2();
}

int Moveable::getLayer(){
	if(mBase)
		return mBase->getTranslation()[2];
	else return 0;
}

glm::vec2 Moveable::getScale(){
	if(mBase)
		return glm::vec2(mBase->getScale());
	else return glm::vec2();
}


} // mgf



















