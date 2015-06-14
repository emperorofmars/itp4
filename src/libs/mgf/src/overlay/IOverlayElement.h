/*
**	Author:		Martin Schwarz
**	Name:		IOverlayElement.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_IOVERLAY_ELEMENT_H
#define MGF_IOVERLAY_ELEMENT_H

#include "../Include.h"
#include "../renderer/Renderer.h"

namespace mgf{

class IOverlayElement{
public:
	virtual ~IOverlayElement(){};

	virtual bool render(std::shared_ptr<Renderer> renderer) = 0;

	virtual bool setName(const std::string &name) = 0;

	virtual void translate(glm::vec2 pos) = 0;
	virtual void setPos(glm::vec2 pos) = 0;
	virtual void setLayer(int layer) = 0;
	virtual void scale(glm::vec2 scale) = 0;
	virtual void setScale(glm::vec2 scale) = 0;

	virtual bool checkIfInsideNDC(glm::vec2 point, float aspectRatio = 1.f){return false;};

	virtual std::string getName() = 0;
	virtual glm::vec2 getPos() = 0;
	virtual int getLayer() = 0;
	virtual glm::vec2 getScale() = 0;
};

} // mgf

#endif // MGF_IOVERLAY_ELEMENT_H











