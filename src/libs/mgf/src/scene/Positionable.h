/*
**	Author:		Martin Schwarz
**	Name:		Positionable.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_POSITIONABLE_H
#define MGF_POSITIONABLE_H

#include "../Include.h"

namespace mgf{

class Positionable{
public:
	Positionable();
	virtual ~Positionable();

	void translate(glm::vec3 data);
	void rotate(float angle, glm::vec3 data);
	void scale(glm::vec3 data);

	void setTranslation(glm::vec3 data);
	void setRotation(glm::mat4 data);
	void setScale(glm::vec3 data);
	void setTRS(glm::mat4 data);

	glm::vec3 getTranslation();
	glm::mat4 getRotation();
	glm::vec3 getScale();
	glm::mat4 getTRS();

protected:
	glm::vec3 mTranslation, mScale;
	glm::mat4 mTRS;
};

} // mgf

#endif // MGF_POSITIONABLE_H











