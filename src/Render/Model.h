#pragma once

#include "World/Mesh.h"
#include "Render/Material.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"

struct CameraData
{
	alignas(16) glm::mat4 Projection;
	alignas(16) glm::mat4 View;
};

class Model
{
public:
	Model();
	Model(const Transform& transform);

	void Init();

	void Load(const std::filesystem::path& directory, const std::filesystem::path& path);

	void Render(Material& material);

	void Free();

	std::vector<Mesh>& GetMeshes() { return mModelMeshes; }
	std::vector<openglTexture>& GetTextures() { return mModelTextures; }

protected:
	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<openglTexture> LoadTextures(aiMaterial* material, aiTextureType type);

protected:
	CameraData mCameraData;
	Transform mTransform;

private:
	std::vector<Mesh> mModelMeshes;

	std::vector<openglTexture> mModelTextures;

	std::filesystem::path mDirectory;
};

