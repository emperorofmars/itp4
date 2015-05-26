/*
**	Author:		Martin Schwarz
**	Name:		IInput.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_IINPUT_H
#define MGF_IINPUT_H

#include "../Include.h"

namespace mgf{

class IInput{
public:
	virtual ~IInput(){};

	virtual void setup(glm::vec3 moveSpeed, glm::vec2 mouseSpeed) = 0;

	virtual void update() = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec2 getMouseRelative() = 0;
	virtual glm::vec2 getMouseAbsolute() = 0;
	virtual glm::bvec3 getMouseClick() = 0;
	virtual float getMouseScroll() = 0;
	virtual bool getQuit() = 0;
};

} // mgf

#endif // MGF_IINPUT_H
