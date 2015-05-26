/*
**	Author:		Martin Schwarz
**	Name:		RayPlane.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "RayPlane.h"

namespace mgf{

glm::vec3 colLinePlane(glm::vec3 lineOrigin, glm::vec3 lineDir, glm::vec3 planeOrigin, glm::vec3 planeNormal){
	return lineOrigin + glm::dot((planeOrigin - lineOrigin), planeNormal) / glm::dot(lineDir, planeNormal) * lineDir;
}

} // mgf
