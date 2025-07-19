#pragma once

#include "World/Mesh.h"
#include "Render/openglShader.h"

class Model
{
public:
	Model();

	void Init();

	void Render(openglShader& shader);

	void Free();

	inline std::vector<Mesh>& GetMeshes() { return mModelMeshes; }

private:
	std::vector<Mesh> mModelMeshes;
};

