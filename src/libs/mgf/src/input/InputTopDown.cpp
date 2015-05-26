/*
**	Author:		Martin Schwarz
**	Name:		InputTopDown.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "InputTopDown.h"

namespace mgf{

InputTopDown::InputTopDown()
	: BaseInput(){}

InputTopDown::~InputTopDown(){
}

void InputTopDown::update(){
	updateEvents();

	int mX, mY;
	SDL_GetRelativeMouseState(&mX, &mY);
	mMouseRelative = glm::vec2(mX, mY);
	SDL_GetMouseState(&mX, &mY);
	mMouseAbsolute = glm::vec2(mX, mY);

	const Uint8 *key = SDL_GetKeyboardState(NULL);
	int f = 0, b = 0, l = 0, r = 0;

	if(key[SDL_SCANCODE_W]){
		f = 1;
	}
	if(key[SDL_SCANCODE_S]){
		b = 1;
	}
	if(key[SDL_SCANCODE_D]){
		r = 1;
	}
	if(key[SDL_SCANCODE_A]){
		l = 1;
	}

	mPos[2] = f - b;
	mPos[1] = mMouseScroll;
	mPos[0] = r - l;

	return;
}

} // mgf



















