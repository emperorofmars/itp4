/*
**	Author:		Martin Schwarz
**	Name:		MouseRay.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_MOUSERAY_H
#define MGF_MOUSERAY_H

#include "../Include.h"

namespace mgf{

glm::vec3 calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec2 screenPoint, glm::vec2 screenSize);
glm::vec3 calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec2 NormalizedScreenPoint);

} // mgf

#endif // MGF_MOUSERAY_H
