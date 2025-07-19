#include "Core/Core.h"
#include "Model.h"

Model::Model()
{
}

void Model::Init()
{
}

void Model::Render(openglShader& shader)
{
	for (auto& mesh : mModelMeshes)
	{
		mesh.Render(shader);
	}
}

void Model::Free()
{
	for (auto& mesh : mModelMeshes)
	{
		mesh.Free();
	}
}
