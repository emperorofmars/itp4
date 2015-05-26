/*
**	Author:		Martin Schwarz
**	Name:		SimpleLoader.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "SimpleLoader.h"

#include "../helper/Helper.h"

namespace mgf{

bool loadMeshToGPU(std::shared_ptr<Mesh> mesh){
	if(!mesh) return false;

	glGenVertexArrays(1, &mesh->mVAO);
	glBindVertexArray(mesh->mVAO);

	if(mesh->mNumIndices > 0){
		GLuint *indices = new GLuint[mesh->mNumIndices];

		for(unsigned int i = 0; i < mesh->mNumIndices; i++){
			indices[i] = (GLuint)mesh->mIndices[i];
		}
		glGenBuffers(1, &mesh->mIndexbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->mIndexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->mNumIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

		delete [] indices;
	}
	else mesh->mIndexbuffer = 0;

	if(mesh->mVertices.size() > 0){
		glGenBuffers(1, &mesh->mVertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->mVertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), &mesh->mVertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
	}

	if(mesh->mNormals.size() > 0){
		glGenBuffers(1, &mesh->mNormalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->mNormalbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), &mesh->mNormals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	}

	for(unsigned int i = 0; i < mesh->mUVBuffer.size(); i++){
		if(mesh->mUV[i].size() > 0){
			glGenBuffers(1, &mesh->mUVBuffer[i]);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->mUVBuffer[i]);
			glBufferData(GL_ARRAY_BUFFER, mesh->mNumVertices * sizeof(aiVector3D), &mesh->mUV[i][0], GL_STATIC_DRAW);
			glVertexAttribPointer(2 + i, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(2 + i);
		}
	}
	glBindVertexArray(0);

	return true;
}

bool loadTextureToGPU(std::shared_ptr<Texture> texture, unsigned int index){
	glActiveTexture(GL_TEXTURE0 + index);	//create opengl texture object
	glGenTextures(1, &texture->mTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if(texture->mImage == NULL){
		texture->mImage = IMG_Load(texture->mName.c_str());
		if(texture->mImage == NULL) return NULL;
	}

	if(texture->mImage != NULL){	//load it to gpu
		glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, texture->mImage->w, texture->mImage->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->mImage->w, texture->mImage->h, GL_RGBA, GL_UNSIGNED_BYTE, texture->mImage->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return false;
}

std::shared_ptr<Texture> loadTextureFromSDLSurface(SDL_Surface *image, unsigned int index){
	if(!image) return NULL;
	std::shared_ptr<Texture> texture(new Texture());
	texture->mImage = image;

	glActiveTexture(GL_TEXTURE0 + index);	//create opengl texture object
	glGenTextures(1, &texture->mTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if(texture->mImage != NULL){	//load it to gpu
		glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, texture->mImage->w, texture->mImage->h);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->mImage->w, texture->mImage->h, GL_RGBA, GL_UNSIGNED_BYTE, texture->mImage->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	return texture;
}


} // mgf



















