/*
**	Author:		Martin Schwarz
**	Name:		InputTopDown.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_INPUT_TOPDOWN_H
#define MGF_INPUT_TOPDOWN_H

#include "../Include.h"
#include "BaseInput.h"

namespace mgf{

class InputTopDown : public BaseInput{
public:
	InputTopDown();
	virtual ~InputTopDown();

	virtual void update();
};

} // mgf

#endif // MGF_INPUT_TOPDOWN_H
