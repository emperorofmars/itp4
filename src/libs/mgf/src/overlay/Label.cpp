/*
**	Author:		Martin Schwarz
**	Name:		Label.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Label.h"

namespace mgf{

Label::Label(const std::string &name)
	: Moveable(name)
{

}

Label::~Label(){
}

bool Label::render(std::shared_ptr<Renderer> renderer){
	return false;
}

bool Label::setText(const std::string &text){
	return false;
}

bool Label::setBackground(const std::string &path){
	return false;
}

bool Label::setBackground(std::shared_ptr<Texture> texture){
	return false;
}

std::string Label::getText(){
	return mText;
}

std::shared_ptr<Texture> Label::getBackground(){
	return mBackground;
}

bool Label::textToTexture(const std::string &text){
	return false;
}


} // mgf



















