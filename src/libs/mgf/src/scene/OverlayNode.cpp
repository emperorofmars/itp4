/*
**	Author:		Martin Schwarz
**	Name:		OverlayNode.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "OverlayNode.h"

namespace mgf{

OverlayNode::OverlayNode(const std::string &name)
	: MeshNode(name)
{
}

OverlayNode::~OverlayNode(){
}

std::shared_ptr<Node> OverlayNode::clone(){
	std::shared_ptr<OverlayNode> ret(new OverlayNode(count_up(mName)));

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

		ret->mMeshes = mMeshes;

		for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
			ret->add(iter->second->clone());
		}
	mMutex.unlock();

	return ret;
}

bool OverlayNode::update(std::shared_ptr<Renderer> renderer){
	return updateImpl(glm::mat4(1), renderer);
}

bool OverlayNode::render(std::shared_ptr<Renderer> renderer){
	return renderImpl(glm::mat4(1), renderer);
}

bool OverlayNode::updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	return true;
}

bool OverlayNode::renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	if(!mVisible) return true;

	transform *= getTRS();

	for(unsigned int i = 0; i < mMeshes.size(); i++){
		if(!renderer->draw2dOverlayMesh(mMeshes[i], transform, mMaterial)){
			LOG_F_ERROR(MGF_LOG_FILE, "Rendering Failed!");
			return false;
		}
	}

	for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
		if(!iter->second->renderImpl(transform, renderer)){
			return false;
		}
	}
	return true;
}

} // mgf



















