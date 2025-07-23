#pragma once

#include "World/Mesh.h"
#include "Render/Material.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"
#include "Physics/3D/Rigidbody.h"
#include "Render/openglUniformBuffer.h"
#include "Algorithims/Bounds.h"

struct CameraData
{
	alignas(16) glm::mat4 Projection;
	alignas(16) glm::mat4 View;
};

class Model
{
public:
	Model();
	Model(const Transform& transform, BoundTypes type = BoundTypes::AABB);

	void Init();

	void Load(const std::filesystem::path& directory, const std::filesystem::path& path);

	void Render(Material& material, const float delta, bool setModel = true, bool render = true);
	void Render(openglShader& shader, const float delta, bool setModel = true, bool render = true);

	void Free();

	std::vector<Mesh>& GetMeshes() { return mModelMeshes; }
	std::vector<openglTexture>& GetTextures() { return mModelTextures; }

	Rigidbody& GetRigidbody() { return mRigidbody; }

protected:
	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<openglTexture> LoadTextures(aiMaterial* material, aiTextureType type);

	openglUniformBuffer mUniformBuffer{};

protected:
	CameraData mCameraData;
	Transform mTransform;
	Rigidbody mRigidbody;
	BoundTypes mBoundsType;

private:
	std::vector<Mesh> mModelMeshes;

	std::vector<openglTexture> mModelTextures;

	std::filesystem::path mDirectory;
};

