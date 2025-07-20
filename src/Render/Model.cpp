#include "Core/Core.h"
#include "Model.h"

Model::Model()
{
}

void Model::Init()
{
}

void Model::Render(Material& material)
{
	for (auto& mesh : mModelMeshes)
	{
		mesh.Render(material);
	}
}

void Model::Free()
{
	for (auto& mesh : mModelMeshes)
	{
		mesh.Free();
	}
}
