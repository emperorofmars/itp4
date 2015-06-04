/*
**	Author:		Martin Schwarz
**	Name:		Button.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Button.h"

#include "../helper/Helper.h"

namespace mgf{

Button::Button(const std::string &name)
	: Label(name)
{
}

Button::~Button(){
}

bool Button::checkIfInsideNDC(glm::vec2 point){
	if(point[0] < getPos()[0] - getScale()[0] / 2 || point[0] > getPos()[0] + getScale()[0] / 2) return false;
	if(point[1] < getPos()[1] - -getScale()[1] / 2 || point[1] > getPos()[1] + -getScale()[1] / 1) return false;
	return true;
}

} // mgf



















