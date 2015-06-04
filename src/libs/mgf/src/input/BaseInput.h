/*
**	Author:		Martin Schwarz
**	Name:		BaseInput.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_BASEINPUT_H
#define MGF_BASEINPUT_H

#include "../Include.h"
#include "IInput.h"

namespace mgf{

class BaseInput : public IInput{
public:
	BaseInput();
	virtual ~BaseInput();

	virtual void setup(glm::vec3 moveSpeed, glm::vec2 mouseSpeed);

	virtual void update();

	virtual glm::vec3 getPosition();
	virtual glm::vec2 getMouseRelative();
	virtual glm::vec2 getMouseRelativeNDC(glm::vec2 screen);
	virtual glm::vec2 getMouseAbsolute();
	virtual glm::vec2 getMouseAbsoluteNDC(glm::vec2 screen);
	virtual glm::bvec3 getMouseClick();
	virtual float getMouseScroll();
	virtual bool getQuit();

protected:
	virtual void updateEvents();

	glm::vec3 mPos;
	glm::vec2 mMouseRelative;
	glm::vec2 mMouseAbsolute;
	glm::bvec3 mMouseClick;
	float mMouseScroll;
	bool mQuit;

	glm::vec3 mMoveSpeed;
	glm::vec2 mMouseSpeed;

	SDL_Event mEvent;
};

} // mgf

#endif // MGF_BASEINPUT_H
