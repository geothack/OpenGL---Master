#pragma once

#include "World/Mesh.h"
#include "Render/Material.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"
#include "Physics/3D/Rigidbody.h"

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

	void Render(Material& material, const float delta);

	void Free();

	std::vector<Mesh>& GetMeshes() { return mModelMeshes; }
	std::vector<openglTexture>& GetTextures() { return mModelTextures; }

	Rigidbody& GetRigidbody() { return mRigidbody; }

protected:
	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<openglTexture> LoadTextures(aiMaterial* material, aiTextureType type);

protected:
	CameraData mCameraData;
	Transform mTransform;
	Rigidbody mRigidbody;


private:
	std::vector<Mesh> mModelMeshes;

	std::vector<openglTexture> mModelTextures;

	std::filesystem::path mDirectory;
};

