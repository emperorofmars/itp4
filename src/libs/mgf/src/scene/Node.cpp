/*
**	Author:		Martin Schwarz
**	Name:		Node.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Node.h"

namespace mgf{

mgfID_t Node::mGlobalID = 0;
std::mutex Node::mGlobalMutex;

Node::Node(const std::string &name){
	LOG_F_TRACE(MGF_LOG_FILE, "Creating Node: ", name);
	mName = name;
	mParentNode = NULL;
	mVisible = true;

	mGlobalMutex.lock();
		mID = mGlobalID;
		mGlobalID++;
		mNumChildren = 0;
	mGlobalMutex.unlock();
}

Node::~Node(){
	LOG_F_TRACE(MGF_LOG_FILE, "Deleting Node: ", mName);
}

std::shared_ptr<Node> Node::clone(){
	std::shared_ptr<Node> ret(new Node(count_up(mName)));

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

		for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
			ret->add(iter->second->clone());
		}
	mMutex.unlock();

	return ret;
}

std::shared_ptr<Node> Node::find(const std::string &name){
	return mChildNodesString[name];
}

std::shared_ptr<Node> Node::getChild(const std::string &name){
	return mChildNodesString[name];
}

bool Node::add(std::shared_ptr<Node> node){
	if(!node) return false;
	if(mChildNodesID[node->getID()] == node ||
		mChildNodesString[node->getName()] == node)
	{
		return false;
	}
	mMutex.lock();
		mChildNodesID[node->getID()] = node;
		mChildNodesString[node->getName()] = node;
		node->mMutex.lock();
			node->mParentNode = this;
		node->mMutex.unlock();
	mMutex.unlock();
	return true;
}

bool Node::remove(const std::string name){
	if(mChildNodesString[name] == NULL) return -1;
	mMutex.lock();
		mChildNodesID.erase(mChildNodesString[name]->getID());
		mChildNodesString.erase(name);
	mMutex.unlock();
	return true;
}

bool Node::remove(unsigned int id){
	if(mChildNodesID[id] == NULL) return -1;
	mMutex.lock();
		mChildNodesID.erase(id);
		mChildNodesString.erase(mChildNodesID[id]->getName());
	mMutex.unlock();
	return true;
}

void Node::setVisible(bool visible){
	mVisible = visible;
	return;
}

bool Node::update(std::shared_ptr<Renderer> renderer){
	renderer->clearLights();
	return updateImpl(glm::mat4(1), renderer);
}

bool Node::render(std::shared_ptr<Renderer> renderer){
	update(renderer);
	return renderImpl(glm::mat4(1), renderer);
}

bool Node::addMesh(std::shared_ptr<Mesh> data){
	return false;
}

bool Node::removeMesh(std::shared_ptr<Mesh> data){
	return false;
}

void Node::setMaterial(std::shared_ptr<Material> material){
	return;
}

void Node::resetMaterial(){
	return;
}

bool Node::setLight(std::shared_ptr<Light> data){
	return false;
}

std::shared_ptr<Light> Node::getLight(){
	return NULL;
}

void Node::setLight(int type, float strenghtDiffuse, float strenghtSpecular, glm::vec3 color,
					glm::vec3 position, glm::vec3 direction, float coneAngle){
	return;
}

mgfID_t Node::getID(){
	return mID;
}

std::string Node::getName(){
	return mName;
}

glm::vec3 Node::getGlobalTranslation(){
	glm::vec3 ret;
	if(mParentNode){
		ret = mParentNode->getGlobalTranslation();
	}
	return ret + mTranslation;
}

glm::mat4 Node::getGlobalRotation(){
	glm::mat4 ret;
	if(mParentNode){
		ret = mParentNode->getGlobalRotation();
	}
	return ret * mTRS;
}

glm::vec3 Node::getGlobalScale(){
	glm::vec3 ret;
	if(mParentNode){
		ret = mParentNode->getGlobalScale();
	}
	return ret + mScale;
}

glm::mat4 Node::getGlobalTRS(){
	glm::mat4 ret;
	if(mParentNode){
		ret = mParentNode->getGlobalTRS();
	}
	return ret * getTRS();
}

void Node::print(unsigned int deepness){
	for(unsigned int i = 0; i < deepness; i++){
		std::cout << "|-";
	}
	std::cout << mName << std::endl;
	for(auto iter = mChildNodesID.begin(); iter != mChildNodesID.end(); iter++){
		iter->second->print(deepness + 1);
	}
	return;
}

bool Node::updateImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
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

bool Node::renderImpl(glm::mat4 transform, std::shared_ptr<Renderer> renderer){
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



















