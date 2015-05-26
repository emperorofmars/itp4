/*
**	Author:		Martin Schwarz
**	Name:		Data.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Data.h"

namespace mgf{

Data::Data(){
}

Data::~Data(){
	mMeshes.clear();
	mMaterials.clear();
	mTextures.clear();
	mLights.clear();
}

} // mgf
















