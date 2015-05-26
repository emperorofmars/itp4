/*
**	Author:		Martin Schwarz
**	Name:		Loader.h
**	Project:	mgf - Mars Graphics Framework
*/

#ifndef MGF_LOADER_H
#define MGF_LOADER_H

#include "../Include.h"
#include "MeshNode.h"
#include "../data/Data.h"

namespace mgf{

class Loader{
public:
	Loader(bool loadIndexed = false, bool loadOnlyToGPU = true);
	~Loader();

	std::shared_ptr<Node> load(const std::string &file);
	void clear();

private:
	std::shared_ptr<Node> loadNodetree(aiNode *ainode);
	bool loadData(const aiScene *scene);

	std::shared_ptr<Mesh> loadMesh(aiMesh *mesh, bool loadToData = false);
	std::shared_ptr<Material> loadMaterial(aiMaterial *material);
	std::shared_ptr<Texture> loadTexture(const std::string &path);
	std::shared_ptr<Light> loadLight(const std::string &path);

	bool loadMeshToGPU(std::shared_ptr<Mesh> mesh);
	bool loadMeshToGPU(std::shared_ptr<Mesh> mgfmesh, aiMesh *aimesh);
	bool loadTextureToGPU(std::shared_ptr<Texture> texture, unsigned int index);

	std::string mFile;

	std::unordered_map<unsigned int, std::shared_ptr<Mesh>> mLoadedMeshes;
	std::unordered_map<unsigned int, std::shared_ptr<Material>> mLoadedMaterials;
	std::unordered_map<std::string, std::shared_ptr<Texture>> mLoadedTextures;

	std::shared_ptr<Data> mData;
	bool mLoadIndexed;
	bool mLoadOnlyToGPU;

	std::mutex mMutex;
};

} // mgf

#endif // MGF_LOADER_H












