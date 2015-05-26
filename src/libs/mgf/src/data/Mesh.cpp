/*
**	Author:		Martin Schwarz
**	Name:		Mesh.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Mesh.h"

namespace mgf{

Mesh::Mesh(){
	mIndexbuffer = 0;
	mVertexbuffer = 0;
	mNormalbuffer = 0;
	mVAO = 0;
	mRenderIndexed = true;
}

Mesh::~Mesh(){
	LOG_F_TRACE(MGF_LOG_FILE, "Deleting VAO: ", mName);

	if(mVAO > 0){
		glBindVertexArray(mVAO);

		if(mIndexbuffer > 0) glDeleteBuffers(1, &mIndexbuffer);
		if(mVertexbuffer > 0) glDeleteBuffers(1, &mVertexbuffer);
		if(mNormalbuffer > 0) glDeleteBuffers(1, &mNormalbuffer);
		for(unsigned int i = 0; i < mUVBuffer.size(); i++){
			if(mUVBuffer[i] > 0) glDeleteBuffers(1, &mUVBuffer[i]);
		}

		glDeleteVertexArrays(1, &mVAO);
		glBindVertexArray(0);
	}
}

} // mgf
















