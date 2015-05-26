/*
**	Author:		Martin Schwarz
**	Name:		InputFPS.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_INPUT_FPS_H
#define MGF_INPUT_FPS_H

#include "../Include.h"
#include "BaseInput.h"

namespace mgf{

class InputFPS : public BaseInput{
public:
	InputFPS();
	virtual ~InputFPS();
};

} // mgf

#endif // MGF_INPUT_FPS_H
