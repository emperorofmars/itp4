/*
**	Author:		Martin Schwarz
**	Name:		Button.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_BUTTON_H
#define MGF_BUTTON_H

#include "../Include.h"
#include "Label.h"

namespace mgf{

class Button : public Label{
public:
	Button(const std::string &name);
	virtual ~Button();

	virtual bool checkIfInsideNDC(glm::vec2 point);
};

} // mgf

#endif // MGF_BUTTON_H











