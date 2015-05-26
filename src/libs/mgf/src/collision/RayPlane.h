/*
**	Author:		Martin Schwarz
**	Name:		RayPlane.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_RAYPLANE_H
#define MGF_RAYPLANE_H

#include "../Include.h"

namespace mgf{

glm::vec3 colLinePlane(glm::vec3 lineOrigin, glm::vec3 lineDir, glm::vec3 planeOrigin, glm::vec3 planeNormal);

} // mgf

#endif // MGF_RAYPLANE_H
