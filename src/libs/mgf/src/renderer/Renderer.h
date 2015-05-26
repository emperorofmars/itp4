/*
**	Author:		Martin Schwarz
**	Name:		Renderer.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_RENDERER_H
#define MGF_RENDERER_H

#include "../Include.h"
#include "../util/Window.h"
#include "../util/ShaderProgram.h"
#include "../camera/ICamera.h"
#include "../data/Data.h"
#include "LightManager.h"

namespace mgf{

class Renderer{
public:
	Renderer();
	Renderer(std::shared_ptr<Window> window,
			 std::shared_ptr<ICamera> camera,
			 std::shared_ptr<ShaderProgram> shaderProgram);
	~Renderer();

	bool setWindow(std::shared_ptr<Window> window);
	bool setCamera(std::shared_ptr<ICamera> camera);
	bool setShaderProgram(std::shared_ptr<ShaderProgram> shaderProgram);

	bool addLight(std::shared_ptr<Light> data, glm::mat4 transform);
	bool clearLights();
	bool drawMesh(std::shared_ptr<Mesh> data, glm::mat4 transform, std::shared_ptr<Material> material);
	bool draw2dOverlayMesh(std::shared_ptr<Mesh> data, glm::mat4 transform, std::shared_ptr<Material> material);

	bool good();

private:
	bool applyMatrix(glm::mat4 data, GLuint loc);
	bool applyMaterial(std::shared_ptr<Material> data);

	std::shared_ptr<Window> mWindow;
	std::shared_ptr<ICamera> mCamera;
	std::shared_ptr<ShaderProgram> mShaderProgram;

	LightManager mLights;
};


} // mgf

#endif // MGF_RENDERER_H
