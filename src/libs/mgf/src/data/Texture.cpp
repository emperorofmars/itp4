/*
**	Author:		Martin Schwarz
**	Name:		Texture.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Texture.h"

namespace mgf{

Texture::Texture(){
	mTextureBuffer = 0;
	mImage = NULL;
}

Texture::~Texture(){
	if(mTextureBuffer > 0) glDeleteTextures(1, &mTextureBuffer);
	mTextureBuffer = 0;
	if(mImage != NULL) SDL_FreeSurface(mImage);
	mImage = NULL;
}

} // mgf
















