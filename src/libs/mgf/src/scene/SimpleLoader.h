/*
**	Author:		Martin Schwarz
**	Name:		SimpleLoader.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_SIMPLELOADER_H
#define MGF_SIMPLELOADER_H

#include "../Include.h"
#include "../data/Data.h"

namespace mgf{

bool loadMeshToGPU(std::shared_ptr<Mesh> mesh);
bool loadTextureToGPU(std::shared_ptr<Texture> texture, unsigned int index = 1);
std::shared_ptr<Texture> loadTextureFromSDLSurface(SDL_Surface *image, unsigned int index = 1);
std::shared_ptr<Texture> loadTextureFromPath(const std::string &path, unsigned int index = 1);

} // mgf

#endif // MGF_SIMPLELOADER_H












