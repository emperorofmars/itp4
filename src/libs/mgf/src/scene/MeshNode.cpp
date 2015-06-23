/*
**	Author:		Martin Schwarz
**	Name:		MeshNode.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "MeshNode.h"

namespace mgf{

MeshNode::MeshNode(const std::string &name)
	: Node(name)
{
}

MeshNode::~MeshNode(){
}

std::shared_ptr<Node> MeshNode::clone(){
	std::shared_ptr<MeshNode> ret(new MeshNode(count_up(mName)));

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

bool MeshNode::addMesh(std::shared_ptr<Mesh> data){
	if(!data) return false;
	mMeshes.push_back(data);
	return true;
}

bool MeshNode::removeMesh(std::shared_ptr<Mesh> data){
	if(!data) return false;
	return true;
}

void MeshNode::setMaterial(std::shared_ptr<Material> material){
	mMaterial = material;
	return;
}

void MeshNode::resetMaterial(){
	mMaterial.reset();
	return;
}

bool MeshNode::update(std::shared_ptr<Renderer> renderer){
	renderer->clearLights();
	return updateImpl(glm::mat4(1), renderer);
}

bool MeshNode::render(std::shared_ptr<Renderer> renderer){
	update(renderer);
	return renderImpl(glm::mat4(1), renderer);
}

bool MeshNode::updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	if(!mVisible) return true;

	transform *= getTRS();
	for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
		if(!iter->second->updateImpl(transform, renderer)){
			LOG_F_ERROR(MGF_LOG_FILE, "Rendering Failed!");
			return false;
		}
	}
	return true;
}

bool MeshNode::renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
	if(!mVisible) return true;

	transform *= getTRS();

	for(unsigned int i = 0; i < mMeshes.size(); i++){
		if(!renderer->drawMesh(mMeshes[i], transform, mMaterial)){
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



















