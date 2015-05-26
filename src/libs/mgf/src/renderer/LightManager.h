/*
**	Author:		Martin Schwarz
**	Name:		LightManager.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_LIGHTMANAGER_H
#define MGF_LIGHTMANAGER_H

#include "../Include.h"
#include "../data/Light.h"
#include "../data/Texture.h"
#include "../scene/SimpleLoader.h"

namespace mgf{

class LightManager{
public:
	LightManager();
	~LightManager();

	void add(std::shared_ptr<Light> light);
	void remove(std::shared_ptr<Light> light);
	void remove(const std::string &name);
	void clear();
	void refresh();

	unsigned int getHeight();

	std::shared_ptr<Light> getLight(const std::string &name);
	std::vector<std::shared_ptr<Light>> getLights();
	std::shared_ptr<Texture> getTexture();

private:
	void assembleTexture();

	std::vector<std::shared_ptr<Light>> mLights;
	std::shared_ptr<Texture> mTexture;
};

} // mgf

#endif // MGF_LIGHTMANAGER_H












