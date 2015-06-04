/*
**	Author:		Martin Schwarz
**	Name:		Helper.h
**	Project:	mgf - Mars Graphics Framework
*/


#ifndef MGF_HELPER_H
#define MGF_HELPER_H

#include "../Include.h"
#include "../data/Mesh.h"
#include "../data/Material.h"

namespace mgf{

std::string vec2_toStr(glm::vec2 data);
std::string vec3_toStr(glm::vec3 data);
std::string vec4_toStr(glm::vec4 data);
std::string mat4_toStr(glm::mat4 data);

std::string count_up(std::string);

std::shared_ptr<Mesh> createPlane();
std::shared_ptr<Mesh> createCube();

} // mgf

#endif // MGF_HELPER_H





