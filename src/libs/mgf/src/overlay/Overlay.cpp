/*
**	Author:		Martin Schwarz
**	Name:		Overlay.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Overlay.h"

namespace mgf{

Overlay::Overlay(){
}

Overlay::~Overlay(){
}

bool Overlay::render(std::shared_ptr<Renderer> renderer){
	for(unsigned int i = 0; i < mElements.size(); i++){
		mElements[i]->render(renderer);
	}
	return true;
}

bool Overlay::add(std::shared_ptr<IOverlayElement> element){
	if(!element) return false;
	mElements.push_back(element);
	return true;
}

bool Overlay::remove(std::shared_ptr<IOverlayElement> element){
	if(!element) return false;
	for(unsigned int i = 0; i < mElements.size(); i++){
		if(mElements[i] == element){
			mElements.erase(mElements.begin() + i);
			break;
		}
	}
	return true;
}

bool Overlay::remove(const std::string &name){
	std::shared_ptr<IOverlayElement> elm = getElement(name);
	if(!elm) return false;
	remove(elm);
	return true;
}

std::shared_ptr<IOverlayElement> Overlay::getMouseOverNDC(glm::vec2 point, float aspectRatio){
	for(unsigned int i = 0; i < mElements.size(); i++){
		if(mElements[i]->checkIfInsideNDC(point, aspectRatio)) return mElements[i];
	}
	return NULL;
}

std::shared_ptr<IOverlayElement> Overlay::getElement(const std::string &name){
	for(unsigned int i = 0; i < mElements.size(); i++){
		if(mElements[i]->getName() == name){
			return mElements[i];
		}
	}
	return NULL;
}

} // mgf



















