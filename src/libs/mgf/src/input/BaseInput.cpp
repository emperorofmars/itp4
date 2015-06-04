/*
**	Author:		Martin Schwarz
**	Name:		BaseInput.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "BaseInput.h"

namespace mgf{

BaseInput::BaseInput(){
	mMouseScroll = 0;
	mQuit = false;
	mMoveSpeed = glm::vec3(1.f, 1.f, 1.f);
	mMouseSpeed = glm::vec2(1.f, 1.f);
}

BaseInput::~BaseInput(){
}

void BaseInput::setup(glm::vec3 moveSpeed, glm::vec2 mouseSpeed){
	mMoveSpeed = moveSpeed;
	mMouseSpeed = mouseSpeed;
	return;
}

void BaseInput::update(){
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
	mPos[0] = r - l;

	return;
}

void BaseInput::updateEvents(){
	mMouseScroll = 0;
	while(SDL_PollEvent(&mEvent) != 0){
		if(mEvent.type == SDL_QUIT) mQuit = true;
		if(mEvent.type == SDL_KEYDOWN){
			switch(mEvent.key.keysym.sym){
			case SDLK_q:
				mQuit = true;
				break;
			case SDLK_ESCAPE:
				if(SDL_GetRelativeMouseMode() == SDL_TRUE){
					SDL_SetRelativeMouseMode(SDL_FALSE);
				}
				else{
					SDL_SetRelativeMouseMode(SDL_TRUE);
				}
				break;
			}
		}
		if(mEvent.type == SDL_KEYUP){
			switch(mEvent.key.keysym.sym){
			case SDLK_q:
				mQuit = false;
				break;
			}
		}
		if(mEvent.type == SDL_MOUSEBUTTONDOWN){
			switch(mEvent.button.button){
			case SDL_BUTTON_LEFT:
				mMouseClick[0] = true;
				break;
			case SDL_BUTTON_MIDDLE:
				mMouseClick[1] = true;
				break;
			case SDL_BUTTON_RIGHT:
				mMouseClick[2] = true;
				break;
			}
		}
		if(mEvent.type == SDL_MOUSEBUTTONUP){
			switch(mEvent.button.button){
			case SDL_BUTTON_LEFT:
				mMouseClick[0] = false;
				break;
			case SDL_BUTTON_MIDDLE:
				mMouseClick[1] = false;
				break;
			case SDL_BUTTON_RIGHT:
				mMouseClick[2] = false;
				break;
			}
		}
		if(mEvent.type == SDL_MOUSEWHEEL){
			mMouseScroll = -mEvent.wheel.y;
		}
	}
	return;
}

glm::vec3 BaseInput::getPosition(){
	return mPos;
}

glm::vec2 BaseInput::getMouseRelative(){
	return mMouseRelative;
}

glm::vec2 BaseInput::getMouseRelativeNDC(glm::vec2 screen){
	return mMouseRelative / screen;
}

glm::vec2 BaseInput::getMouseAbsolute(){
	return mMouseAbsolute;
}

glm::vec2 BaseInput::getMouseAbsoluteNDC(glm::vec2 screen){
	return mMouseAbsolute / screen;
}

glm::bvec3 BaseInput::getMouseClick(){
	return mMouseClick;
}

float BaseInput::getMouseScroll(){
	return mMouseScroll;
}

bool BaseInput::getQuit(){
	return mQuit;
}

} // mgf



















