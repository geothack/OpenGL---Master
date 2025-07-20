#pragma once

#include "World/Mesh.h"
#include "Render/Material.h"

class Model
{
public:
	Model();

	void Init();

	void Render(Material& material);

	void Free();

	inline std::vector<Mesh>& GetMeshes() { return mModelMeshes; }

private:
	std::vector<Mesh> mModelMeshes;
};

