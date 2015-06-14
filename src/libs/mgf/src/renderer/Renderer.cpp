/*
**	Author:		Martin Schwarz
**	Name:		Renderer.cpp
**	Project:	mgf - Mars Graphics Framework
*/

#include "Renderer.h"

namespace mgf{

Renderer::Renderer(std::shared_ptr<Window> window,
		 std::shared_ptr<ICamera> camera,
		 std::shared_ptr<ShaderProgram> shaderProgram)
{
	mWindow = window;
	mCamera = camera;
	mShaderProgram = shaderProgram;
}

Renderer::~Renderer(){
}

bool Renderer::setWindow(std::shared_ptr<Window> window){
	if(!window) return false;
	mWindow = window;
	return true;
}

bool Renderer::setCamera(std::shared_ptr<ICamera> camera){
	if(!camera) return false;
	mCamera = camera;
	return true;
}

bool Renderer::setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram){
	if(!shaderProgram) return false;
	mShaderProgram = shaderProgram;
	return true;
}

bool Renderer::addLight(std::shared_ptr<Light> data, glm::mat4 transform){
	if(!data) return false;
	std::shared_ptr<Light> light(new Light());
	*light = *data;
	light->mPosition = glm::vec3(transform * glm::vec4(light->mPosition, 1));
	light->mDirection = glm::vec3(glm::inverseTranspose(transform) * glm::vec4(light->mDirection, 0));
	mLights.add(light);
	return true;
}

bool Renderer::clearLights(){
	mLights.clear();
	return true;
}

bool Renderer::drawMesh(std::shared_ptr<Mesh> data, glm::mat4 transform, std::shared_ptr<Material> material){
	mWindow->use();
	mShaderProgram->use();

	if(!data){
		LOG_F_ERROR(MGF_LOG_FILE, "data is NULL!");
		return false;
	}
	if(!applyMatrix(transform, mShaderProgram->get(MATRIX_MODEL))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix MODEL Failed!");
		return false;
	}
	if(!applyMatrix(mCamera->getVP(), mShaderProgram->get(MATRIX_VP))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix VP Failed!");
		return false;
	}
	if(!applyMatrix(glm::inverseTranspose(transform), mShaderProgram->get(MATRIX_NORM))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix VP Failed!");
		return false;
	}
	if(material){
		if(!applyMaterial(material)){
			LOG_F_ERROR(MGF_LOG_FILE, "applyMaterial for Mesh material Failed!");
			return false;
		}
	}
	else{
		if(!applyMaterial(data->mMaterial)){
			LOG_F_ERROR(MGF_LOG_FILE, "applyMaterial for supplied Failed!");
			return false;
		}
	}
	if(data->mVAO == 0){
		LOG_F_ERROR(MGF_LOG_FILE, "VAO is 0!");
		return false;
	}

	glBindVertexArray(data->mVAO);

    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(data->mRenderIndexed){
		//LOG_F_TRACE(MGF_LOG_FILE, "Drawing ", data->mNumIndices, " Elements");
		glDrawElements(GL_TRIANGLES, data->mNumIndices * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	}
	else{
		//LOG_F_TRACE(MGF_LOG_FILE, "Drawing ", data->mNumVertices, " Vertices");
		glDrawArrays(GL_TRIANGLES, 0, data->mNumVertices * sizeof(GLuint));
	}
	glBindVertexArray(0);

	return true;
}

bool Renderer::draw2dOverlayMesh(std::shared_ptr<Mesh> data, glm::mat4 transform, std::shared_ptr<Material> material){
	mWindow->use();
	mShaderProgram->use();

	if(!data){
		LOG_F_ERROR(MGF_LOG_FILE, "data is NULL!");
		return false;
	}
	//transform[3][1] /= mWindow->getAspectRatio();
	if(!applyMatrix(transform, mShaderProgram->get(MATRIX_MODEL))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix MODEL Failed!");
		return false;
	}
	glm::mat4 vp = glm::ortho(0.f, 1.f, 1.f / mWindow->getAspectRatio(), 0.f, 10.f, -10.f) *
			glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	if(!applyMatrix(vp, mShaderProgram->get(MATRIX_VP))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix VP Failed!");
		return false;
	}
	if(!applyMatrix(glm::inverseTranspose(transform), mShaderProgram->get(MATRIX_NORM))){
		LOG_F_ERROR(MGF_LOG_FILE, "applyMatrix VP Failed!");
		return false;
	}
	if(material){
		if(!applyMaterial(material)){
			LOG_F_ERROR(MGF_LOG_FILE, "applyMaterial for Mesh material Failed!");
			return false;
		}
	}
	else{
		if(!applyMaterial(data->mMaterial)){
			LOG_F_ERROR(MGF_LOG_FILE, "applyMaterial for supplied Failed!");
			return false;
		}
	}
	if(data->mVAO == 0){
		LOG_F_ERROR(MGF_LOG_FILE, "VAO is 0!");
		return false;
	}

	glBindVertexArray(data->mVAO);

	glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if(data->mRenderIndexed){
		//LOG_F_TRACE(MGF_LOG_FILE, "Drawing ", data->mNumIndices, " Elements");
		glDrawElements(GL_TRIANGLES, data->mNumIndices * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	}
	else{
		//LOG_F_TRACE(MGF_LOG_FILE, "Drawing ", data->mNumVertices, " Vertices");
		glDrawArrays(GL_TRIANGLES, 0, data->mNumVertices * sizeof(GLuint));
	}
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glBindVertexArray(0);

	return true;
}

bool Renderer::good(){
	if(mWindow && mCamera && mShaderProgram) return true;
	return false;
}

bool Renderer::applyMatrix(glm::mat4 data, GLuint loc){
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data));
	return true;
}

bool Renderer::applyMaterial(std::shared_ptr<Material> data){
	if(!good()) return false;
	if(!data) return false;

	GLuint loc = mShaderProgram->get(MATERIAL_COLOR_DIFFUSE);
	glUniform4fv(loc, 1, glm::value_ptr(data->mDiffuseColor));

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "material.specular");
	glUniform4fv(loc, 1, glm::value_ptr(data->mSpecularColor));

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "material.ambient");
	glUniform4fv(loc, 1, glm::value_ptr(data->mAmbientColor));

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "material.emissive");
	glUniform4fv(loc, 1, glm::value_ptr(data->mEmissiveColor));

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "material.shininess");
	glUniform1f(loc, data->mShininess);

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "material.shadingType");
	glUniform1f(loc, data->mShadingType);

	float alpha = 1.f;
	loc = mShaderProgram->get(MATERIAL_ALPHA);
	glUniform1f(loc, alpha);

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "numlights");
	glUniform1i(loc, mLights.getHeight());


	loc = glGetUniformLocation(mShaderProgram->getProgram(), "cameraPos");
	glUniform4fv(loc, 1, glm::value_ptr(glm::vec4(mCamera->getPos(), 1)));

	loc = glGetUniformLocation(mShaderProgram->getProgram(), "lights");
	glUniform1i(loc, 0);
	loc = glGetUniformLocation(mShaderProgram->getProgram(), "tex");
	glUniform1i(loc, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mLights.getTexture()->mTextureBuffer);

	float has_texture;
	if(data->mDiffuseTextures.size() > 0){
		has_texture = 1.f;
		glActiveTexture(GL_TEXTURE0 + 1);
		if(data->mDiffuseTextures[0])
			glBindTexture(GL_TEXTURE_2D, data->mDiffuseTextures[0]->mTextureBuffer);
		else
			has_texture = 0.f;
	}
	else{
		has_texture = 0.f;
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	loc = mShaderProgram->get(MATERIAL_HAS_TEXTURE);
	glUniform1f(loc, has_texture);

	return true;
}


} // mgf
