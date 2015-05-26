/*
**	Author:		Martin Schwarz
**	Name:		Moveable.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_MOVEABLE_H
#define MGF_MOVEABLE_H

#include "../Include.h"
#include "IOverlayElement.h"
#include "../scene/OverlayNode.h"
#include "../helper/Helper.h"

namespace mgf{

class Moveable : public IOverlayElement{
public:
	Moveable(const std::string &name);
	virtual ~Moveable();

	virtual bool render(std::shared_ptr<Renderer> renderer);

	virtual bool setName(const std::string &name);

	virtual void translate(glm::vec2 pos);
	virtual void setPos(glm::vec2 pos);
	virtual void setLayer(int layer);
	virtual void scale(glm::vec2 scale);
	virtual void setScale(glm::vec2 scale);

	virtual std::string getName();
	virtual glm::vec2 getPos();
	virtual int getLayer();
	virtual glm::vec2 getScale();

private:
	std::shared_ptr<OverlayNode> mBase;
};

} // mgf

#endif // MGF_MOVEABLE_H











