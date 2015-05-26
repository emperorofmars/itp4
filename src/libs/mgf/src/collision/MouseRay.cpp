/*
**	Author:		Martin Schwarz
**	Name:		MouseRay.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "MouseRay.h"

namespace mgf{

glm::vec3 calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec2 screenPoint, glm::vec2 screenSize){
	glm::vec2 normalized((2.f * screenPoint[0]) / screenSize[0] - 1.f, 1.f - (2.f * screenPoint[1]) / screenSize[1]);
	return calculateMouseRay(projectionMatrix, viewMatrix, normalized);
}

glm::vec3 calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec2 NormalizedScreenPoint){
	glm::vec4 ret(NormalizedScreenPoint[0], NormalizedScreenPoint[1], -1.f, 1.f);
	ret = glm::inverse(projectionMatrix) * ret;
	ret[2] = -1.f;
	ret[3] = 0.f;
	ret = glm::inverse(viewMatrix) * ret;
	ret = glm::normalize(ret);
	return glm::vec3(ret);
}

} // mgf
