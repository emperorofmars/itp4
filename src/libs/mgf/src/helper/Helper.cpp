/*
**	Author:		Martin Schwarz
**	Name:		Helper.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Helper.h"

namespace mgf{

std::string vec2_toStr(glm::vec2 data){
	std::stringstream res;
	res << "( " << data[0] << ", " << data[1] << " )";
	return res.str();
}

std::string vec3_toStr(glm::vec3 data){
	std::stringstream res;
	res << "( " << data[0] << ", " << data[1] << ", " << data[2] << " )";
	return res.str();
}

std::string vec4_toStr(glm::vec4 data){
	std::stringstream res;
	res << "( " << data[0] << ", " << data[1] << ", " << data[2] << ", " << data[3] << " )";
	return res.str();
}

std::string mat4_toStr(glm::mat4 data){
	std::stringstream res;
	res << "( " << data[0][0] << ", " << data[1][0] << ", " << data[2][0] << ", " << data[3][0] << " )" << std::endl;
	res << "( " << data[0][1] << ", " << data[1][1] << ", " << data[2][1] << ", " << data[3][1] << " )" << std::endl;
	res << "( " << data[0][2] << ", " << data[1][2] << ", " << data[2][2] << ", " << data[3][2] << " )" << std::endl;
	res << "( " << data[0][3] << ", " << data[1][3] << ", " << data[2][3] << ", " << data[3][3] << " )" << std::endl;
	return res.str();
}

std::string count_up(std::string data){
	return data.append(".001");
}

std::shared_ptr<Mesh> createPlane(){
	std::shared_ptr<Mesh> ret(new Mesh);
	ret->mName = "Plane";
	ret->mRenderIndexed = false;

	ret->mVertices.push_back(glm::vec3(0.5f, 0.5f, 0.f));
	ret->mVertices.push_back(glm::vec3(0.5f, -0.5f, 0.f));
	ret->mVertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));
	ret->mVertices.push_back(glm::vec3(-0.5f, 0.5f, 0.f));
	ret->mVertices.push_back(glm::vec3(0.5f, 0.5f, 0.f));
	ret->mVertices.push_back(glm::vec3(-0.5f, -0.5f, 0.f));

	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));
	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));
	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));
	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));
	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));
	ret->mNormals.push_back(glm::vec3(0.f, 0.f, 1.f));

	ret->mUV.resize(1);
	ret->mUV[0].push_back(glm::vec3(1.f, 1.f, 0.f));
	ret->mUV[0].push_back(glm::vec3(1.f, 0.f, 0.f));
	ret->mUV[0].push_back(glm::vec3(0.f, 0.f, 0.f));
	ret->mUV[0].push_back(glm::vec3(0.f, 1.f, 0.f));
	ret->mUV[0].push_back(glm::vec3(1.f, 1.f, 0.f));
	ret->mUV[0].push_back(glm::vec3(0.f, 0.f, 0.f));

	ret->mNumVertices = ret->mVertices.size();
	ret->mNumNormals = ret->mNormals.size();
	ret->mNumUV.resize(1);
	ret->mNumUV[0] = ret->mUV[0].size();

	std::shared_ptr<Material> mat(new Material);
	mat->mDiffuseColor = glm::vec4(0.8f, 0.5f, 0.1f, 1.f);
	ret->mMaterial = mat;

	glGenVertexArrays(1, &ret->mVAO);
	glBindVertexArray(ret->mVAO);

	glGenBuffers(1, &ret->mVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ret->mVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, ret->mNumVertices * sizeof(glm::vec3), &ret->mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ret->mNormalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ret->mNormalbuffer);
	glBufferData(GL_ARRAY_BUFFER, ret->mNumNormals * sizeof(glm::vec3), &ret->mNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	ret->mUVBuffer.resize(1);
	glGenBuffers(1, &ret->mUVBuffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, ret->mUVBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, ret->mNumUV[0] * sizeof(glm::vec3), &ret->mUV[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2 , 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	return ret;
}

std::shared_ptr<Mesh> createCube(){
	std::shared_ptr<Mesh> ret(new Mesh);
	ret->mName = "TestCube";
	ret->mRenderIndexed = true;

	ret->mVertices.push_back(glm::vec3(-1.f, -1.f, -1.f));
	ret->mVertices.push_back(glm::vec3(-1.f, 1.f, -1.f));
	ret->mVertices.push_back(glm::vec3(1.f, -1.f, -1.f));
	ret->mVertices.push_back(glm::vec3(1.f, 1.f, -1.f));
	ret->mVertices.push_back(glm::vec3(-1.f, -1.f, 1.f));
	ret->mVertices.push_back(glm::vec3(-1.f, 1.f, 1.f));
	ret->mVertices.push_back(glm::vec3(1.f, -1.f, 1.f));
	ret->mVertices.push_back(glm::vec3(1.f, 1.f, 1.f));

	ret->mIndices.push_back(0);
	ret->mIndices.push_back(1);
	ret->mIndices.push_back(2);
	ret->mIndices.push_back(3);
	ret->mIndices.push_back(2);
	ret->mIndices.push_back(1);

	ret->mIndices.push_back(6);
	ret->mIndices.push_back(5);
	ret->mIndices.push_back(4);
	ret->mIndices.push_back(5);
	ret->mIndices.push_back(6);
	ret->mIndices.push_back(7);

	ret->mIndices.push_back(4);
	ret->mIndices.push_back(1);
	ret->mIndices.push_back(0);
	ret->mIndices.push_back(1);
	ret->mIndices.push_back(4);
	ret->mIndices.push_back(5);

	ret->mIndices.push_back(0);
	ret->mIndices.push_back(2);
	ret->mIndices.push_back(4);
	ret->mIndices.push_back(6);
	ret->mIndices.push_back(4);
	ret->mIndices.push_back(2);

	ret->mIndices.push_back(5);
	ret->mIndices.push_back(3);
	ret->mIndices.push_back(1);
	ret->mIndices.push_back(3);
	ret->mIndices.push_back(5);
	ret->mIndices.push_back(7);

	ret->mIndices.push_back(2);
	ret->mIndices.push_back(3);
	ret->mIndices.push_back(6);
	ret->mIndices.push_back(3);
	ret->mIndices.push_back(7);
	ret->mIndices.push_back(6);

	ret->mNumIndices = ret->mIndices.size();
	ret->mNumVertices = ret->mVertices.size();
	std::shared_ptr<Material> mat(new Material);
	mat->mDiffuseColor = glm::vec4(0.8f, 0.5f, 0.1f, 1.f);
	ret->mMaterial = mat;

	glGenVertexArrays(1, &ret->mVAO);
	glBindVertexArray(ret->mVAO);

	GLuint *indices = new GLuint[ret->mNumIndices];
	for(unsigned int i = 0; i < ret->mNumIndices; i++){
		indices[i] = (GLuint)ret->mIndices[i];
	}

	glGenBuffers(1, &ret->mIndexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret->mIndexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ret->mNumIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

	delete [] indices;

	glGenBuffers(1, &ret->mVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ret->mVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, ret->mNumVertices * sizeof(glm::vec3), &ret->mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return ret;
}

} // mgf












