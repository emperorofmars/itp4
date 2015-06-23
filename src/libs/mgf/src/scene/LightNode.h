/*
**	Author:		Martin Schwarz
**	Name:		LightNode.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_LIGHTNODE_H
#define MGF_LIGHTNODE_H

#include "Node.h"
#include "../data/Data.h"

namespace mgf{

class LightNode: public Node{
public:
	LightNode(const std::string &name = "", std::shared_ptr<Light> data = NULL);
	~LightNode();

	virtual std::shared_ptr<Node> clone();

	virtual bool setLight(std::shared_ptr<Light> data);
	virtual std::shared_ptr<Light> getLight();

	virtual void setLight(int type = 1, float strenghtDiffuse = 1, float strenghtSpecular = 1, glm::vec3 color = {1.f, 1.f, 1.f},
						glm::vec3 position = {1.f, 1.f, 1.f}, glm::vec3 direction = {1.f, 1.f, 1.f}, float coneAngle = 30);

	virtual bool update(std::shared_ptr<Renderer> renderer);
	virtual bool render(std::shared_ptr<Renderer> renderer);

protected:
	virtual bool updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);
	virtual bool renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer);

	std::shared_ptr<Light> mLight;
};

} // mgf

#endif // MGF_LIGHTNODE_H











