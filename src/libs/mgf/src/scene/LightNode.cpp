/*
**	Author:		Martin Schwarz
**	Name:		LightNode.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "LightNode.h"

namespace mgf{

LightNode::LightNode(const std::string &name, std::shared_ptr<Light> data)
	: Node(name)
{
	if(!data){
		mLight.reset(new Light());
		mLight->mActive = 0;
		return;
	}
	mLight = data;
}

LightNode::~LightNode(){
}

std::shared_ptr<Node> LightNode::clone(){
	std::shared_ptr<LightNode> ret(new LightNode(count_up(mName)));

	mGlobalMutex.lock();
		ret->mID = mGlobalID;
		mGlobalID++;
	mGlobalMutex.unlock();

	mMutex.lock();
		ret->mName = mName;
		ret->mParentNode = mParentNode;

		ret->mTranslation = mTranslation;
		ret->mScale = mScale;
		ret->mTRS = mTRS;

		ret->mLight = mLight;

		for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
			ret->add(iter->second->clone());
		}
	mMutex.unlock();

	return ret;
}

bool LightNode::setLight(std::shared_ptr<Light> data){
	if(!data) return false;
	mLight = data;
	return true;
}

std::shared_ptr<Light> LightNode::getLight(){
	return mLight;
}

void LightNode::setLight(int type, float strenghtDiffuse, float strenghtSpecular, glm::vec3 color,
					glm::vec3 position, glm::vec3 direction, float coneAngle)
{
	mLight->mType = type;
	mLight->mActive = 1;
	mLight->mStrengthDiffuse = strenghtDiffuse;
	mLight->mStrengthSpecular = strenghtSpecular;
	mLight->mColor = color;
	mLight->mPosition = position;
	mLight->mDirection = direction;
	mLight->mConeAngle = coneAngle;
	return;
}

bool LightNode::update(std::shared_ptr<Renderer> renderer){
	renderer->clearLights();
	return updateImpl(glm::mat4(1), renderer);
}

bool LightNode::render(std::shared_ptr<Renderer> renderer){
	update(renderer);
	return renderImpl(glm::mat4(1), renderer);
}

bool LightNode::updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	if(!mVisible) return true;

	transform *= getTRS();

	renderer->addLight(mLight, transform);

	for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
		if(!iter->second->updateImpl(transform, renderer)){
			LOG_F_ERROR(MGF_LOG_FILE, "Rendering Failed!");
			return false;
		}
	}
	return true;
}

bool LightNode::renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	if(!mVisible) return true;

	transform *= getTRS();
	for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
		if(!iter->second->renderImpl(transform, renderer)){
			LOG_F_ERROR(MGF_LOG_FILE, "Rendering Failed!");
			return false;
		}
	}
	return true;
}

} // mgf



















