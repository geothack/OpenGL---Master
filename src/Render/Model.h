#pragma once

#include "World/Mesh.h"
#include "Render/Material.h"

struct CameraData
{
	alignas(16) glm::mat4 Projection;
	alignas(16) glm::mat4 View;
};

class Model
{
public:
	Model();

	void Init();

	void Render(Material& material);

	void Free();

	inline std::vector<Mesh>& GetMeshes() { return mModelMeshes; }

protected:
	CameraData mCameraData;

private:
	std::vector<Mesh> mModelMeshes;
};

