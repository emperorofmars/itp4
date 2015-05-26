/*
**	Author:		Martin Schwarz
**	Name:		OverlayNode.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_OVERLAYNODE_H
#define MGF_OVERLAYNODE_H

#include "MeshNode.h"
#include "../data/Data.h"

namespace mgf{

class OverlayNode : public MeshNode{
public:
	OverlayNode(const std::string &name = "");
	~OverlayNode();

	virtual std::shared_ptr<Node> clone();

	virtual bool render(std::shared_ptr<Renderer> renderer);
	virtual bool update(std::shared_ptr<Renderer> renderer);

protected:
	virtual bool updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);
	virtual bool renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);
};

} // mgf

#endif // MGF_OVERLAYNODE_H











