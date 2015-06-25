/*
**	Author:		Martin Schwarz
**	Name:		Label.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Label.h"

namespace mgf{

Label::Label(const std::string &name)
	: Moveable(name)
{
	mTop.reset(new OverlayNode("Top"));
	mTop->setVisible(false);
	mBase->add(mTop);
	mTop->translate(glm::vec3(0.f, 0.f, 1.f));
	std::shared_ptr<Mesh> plane(createPlane());
	plane->mMaterial->mDiffuseColor = glm::vec4(0.1, 0.5, 0.5, 1);
	plane->mMaterial->mShadingType = 0;
	mTopMat = plane->mMaterial;
	mTop->addMesh(plane);
	mFont = NULL;
	mSize = 220;
	mColor = glm::vec3(0.5, 0.5, 0.5);
}

Label::~Label(){
	TTF_CloseFont(mFont);
	mFont = NULL;
}

bool Label::render(std::shared_ptr<Renderer> renderer){
	if(mBase)
		return mBase->render(renderer);
	else return false;
}

bool Label::setText(const std::string &text){
	mText = text;
	return textToTexture();
}

bool Label::setFont(const std::string &font){
	mFont = TTF_OpenFont(font.c_str(), 128);//(int)mSize);
	if(!mFont){
		LOG_F_ERROR(MGF_LOG_FILE, "Failed to open Font!");
		return false;
	}
	return textToTexture();
}

bool Label::setFont(TTF_Font *font){
	if(!font) return false;
	TTF_CloseFont(mFont);
	mFont = font;
	return textToTexture();
}

bool Label::setColor(glm::vec3 color){
	mColor = color;
	return textToTexture();
}

bool Label::setTextSize(float size){
	mSize = size;
	return textToTexture();
}

bool Label::setBackground(const std::string &path){
	mBaseMat->mDiffuseTextures.resize(1);
	mBaseMat->mDiffuseTextures[0] = loadTextureFromPath(path);
	if(mBaseMat->mDiffuseTextures[0]) return true;
	return false;
}

bool Label::setBackground(std::shared_ptr<Texture> texture){
	mBaseMat->mDiffuseTextures.resize(1);
	mBaseMat->mDiffuseTextures[0] = texture;
	if(mBaseMat->mDiffuseTextures[0]) return true;
	return false;
}

std::string Label::getText(){
	return mText;
}

std::shared_ptr<Texture> Label::getBackground(){
	if(mBaseMat->mDiffuseTextures.size() > 0)
		return mBaseMat->mDiffuseTextures[0];
	return NULL;
}

int Label::nextPow2(int num){
	int pow = 2, next = pow * 2;
	while((next *= 2) <= num) pow *= 2;
	return pow * 2;
}

bool Label::textToTexture(){
	if(!mFont){
		mTop->setVisible(false);
		LOG_F_INFO(MGF_LOG_FILE, "Failed to create text: no Font");
		return false;
	}
	if(mText.size() == 0){
		mTop->setVisible(false);
		LOG_F_INFO(MGF_LOG_FILE, "Failed to create text: no Text");
		return false;
	}
	SDL_Color color;
	color.r = mColor[0] * 255;
	color.g = mColor[1] * 255;
	color.b = mColor[2] * 255;
	color.a = 255;
	SDL_Surface *img = TTF_RenderText_Solid(mFont, mText.c_str(), color);
	if(!img){
		mTop->setVisible(false);
		LOG_F_ERROR(MGF_LOG_FILE, "Failed to create text: could not create image");
		return false;
	}
	SDL_Surface *realimg = SDL_CreateRGBSurface(0, nextPow2(img->w) * 2, nextPow2(img->h) * 2, 32,
					0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
					//img->format->Rmask, img->format->Gmask, img->format->Bmask, img->format->Amask);

	SDL_Rect dest = {(realimg->w - img->w) / 2, (realimg->h - img->h) / 2, nextPow2(img->w), nextPow2(img->h)};
	SDL_BlitSurface(img, NULL, realimg, &dest);

	std::shared_ptr<Texture> tex = loadTextureFromSDLSurface(realimg);
	if(!tex){
		mTop->setVisible(false);
		LOG_F_ERROR(MGF_LOG_FILE, "Failed to create text: could not load texture");
		return false;
	}
	mTopMat->mDiffuseTextures.resize(1);
	mTopMat->mDiffuseTextures[0] = tex;

	mTop->setVisible(true);

	LOG_F_INFO(MGF_LOG_FILE, "Text created successfully!");
	return true;
}


} // mgf



















