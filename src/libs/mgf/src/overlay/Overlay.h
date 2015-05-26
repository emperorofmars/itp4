/*
**	Author:		Martin Schwarz
**	Name:		Overlay.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_OVERLAY_H
#define MGF_OVERLAY_H

#include "../Include.h"
#include "Moveable.h"

namespace mgf{

class Overlay : public Moveable{
public:
	Overlay();
	~Overlay();

	virtual bool render();

	bool addElement(std::shared_ptr<IOverlayElement> element);
	bool removeElement(std::shared_ptr<IOverlayElement> element);
	bool removeElement(std::string name);

	std::shared_ptr<IOverlayElement> getMouseOver(glm::vec2 ndcPos);

	std::shared_ptr<IOverlayElement> getElement(const std::string &name);

private:
	std::vector<std::shared_ptr<IOverlayElement>> mElements;
};

} // mgf

#endif // MGF_OVERLAY_H











