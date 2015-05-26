/*
**	Author:		Martin Schwarz
**	Name:		LightManager.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "LightManager.h"

namespace mgf{

LightManager::LightManager(){
	mTexture.reset(new Texture());
}

LightManager::~LightManager(){
}

void LightManager::add(std::shared_ptr<Light> light){
	if(!light) return;
	mLights.push_back(light);
	assembleTexture();
	return;
}

void LightManager::remove(std::shared_ptr<Light> light){
	for(unsigned int i = 0; i < mLights.size(); i++){
		if(mLights[i] == light){
			mLights.erase(mLights.begin() + i);
			break;
		}
	}
	assembleTexture();
	return;
}

void LightManager::remove(const std::string &name){
	for(unsigned int i = 0; i < mLights.size(); i++){
		if(mLights[i]->mName == name){
			mLights.erase(mLights.begin() + i);
			break;
		}
	}
	assembleTexture();
	return;
}

void LightManager::clear(){
	mLights.clear();
	mTexture.reset(new Texture());
	return;
}

void LightManager::refresh(){
	assembleTexture();
	return;
}

unsigned int LightManager::getHeight(){
	return mLights.size();
}

std::shared_ptr<Light> LightManager::getLight(const std::string &name){
	for(unsigned int i = 0; i < mLights.size(); i++){
		if(mLights[i]->mName == name){
			return mLights[i];
		}
	}
	return NULL;
}

std::vector<std::shared_ptr<Light>> LightManager::getLights(){
	return mLights;
}

std::shared_ptr<Texture> LightManager::getTexture(){
	return mTexture;
}

void LightManager::assembleTexture(){
	mTexture.reset(new Texture());
	if(mLights.size() > 0){
		float lightTexture[mLights.size()][4][4];

		for(unsigned int i = 0; i < mLights.size(); i++){
			lightTexture[i][0][0] = mLights[i]->mActive;
			lightTexture[i][0][1] = mLights[i]->mType;
			lightTexture[i][0][2] = mLights[i]->mStrengthDiffuse;
			lightTexture[i][0][3] = mLights[i]->mStrengthSpecular;

			lightTexture[i][1][0] = mLights[i]->mColor[0];
			lightTexture[i][1][1] = mLights[i]->mColor[1];
			lightTexture[i][1][2] = mLights[i]->mColor[2];
			lightTexture[i][1][3] = 1;

			lightTexture[i][2][0] = mLights[i]->mPosition[0];
			lightTexture[i][2][1] = mLights[i]->mPosition[1];
			lightTexture[i][2][2] = mLights[i]->mPosition[2];
			lightTexture[i][2][3] = 1;

			lightTexture[i][3][0] = mLights[i]->mDirection[0];
			lightTexture[i][3][1] = mLights[i]->mDirection[1];
			lightTexture[i][3][2] = mLights[i]->mDirection[2];
			lightTexture[i][3][3] = 0;
		}

		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &mTexture->mTextureBuffer);
		glBindTexture(GL_TEXTURE_2D, mTexture->mTextureBuffer);

		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 4, mLights.size());
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 4, mLights.size(), GL_RGBA, GL_FLOAT, lightTexture);
	}
	return;
}

} // mgf









