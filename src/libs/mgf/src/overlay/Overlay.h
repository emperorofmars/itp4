/*
**	Author:		Martin Schwarz
**	Name:		Overlay.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_OVERLAY_H
#define MGF_OVERLAY_H

#include "../Include.h"
#include "IOverlayElement.h"

namespace mgf{

class Overlay{
public:
	Overlay();
	~Overlay();

	bool render(std::shared_ptr<Renderer> renderer);

	bool add(std::shared_ptr<IOverlayElement> element);
	bool remove(std::shared_ptr<IOverlayElement> element);
	bool remove(const std::string &name);

	std::shared_ptr<IOverlayElement> getMouseOverNDC(glm::vec2 point, float aspectRatio = 1);

	std::shared_ptr<IOverlayElement> getElement(const std::string &name);

private:
	std::vector<std::shared_ptr<IOverlayElement>> mElements;
};

} // mgf

#endif // MGF_OVERLAY_H











