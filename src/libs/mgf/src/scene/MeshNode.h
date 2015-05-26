/*
**	Author:		Martin Schwarz
**	Name:		MeshNode.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_MESHNODE_H
#define MGF_MESHNODE_H

#include "Node.h"
#include "../data/Data.h"

namespace mgf{

class MeshNode: public Node{
public:
	MeshNode(const std::string &name = "");
	~MeshNode();

	virtual std::shared_ptr<Node> clone();

	virtual bool addMesh(std::shared_ptr<Mesh> data);
	virtual bool removeMesh(std::shared_ptr<Mesh> data);

	virtual void setMaterial(std::shared_ptr<Material> material);
	virtual void resetMaterial();

	virtual bool update(std::shared_ptr<Renderer> renderer);
	virtual bool render(std::shared_ptr<Renderer> renderer);

protected:
	virtual bool updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);
	virtual bool renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);

	std::vector<std::shared_ptr<Mesh>> mMeshes;
	std::shared_ptr<Material> mMaterial;
};

} // mgf

#endif // MGF_MESHNODE_H











