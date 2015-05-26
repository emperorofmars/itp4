/*
**	Author:		Martin Schwarz
**	Name:		Data.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_DATA_H
#define MGF_DATA_H

#include "../Include.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Light.h"

namespace mgf{

class Data{
public:
	Data();
	~Data();

	std::vector<std::shared_ptr<Mesh>> mMeshes;
	std::vector<std::shared_ptr<Material>> mMaterials;
	std::vector<std::shared_ptr<Texture>> mTextures;
	std::vector<std::shared_ptr<Light>> mLights;
};

} // mgf

#endif // MGF_DATA_H








