#pragma once

#include "Render/openglTexture.h"
#include "Render/Material.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TextureCoordinates;

	static std::vector<Vertex> GenerateList(const float* vertice, const int numVertices);
};

class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);


	void Render(Material& material);

	void Free() const;

private:
	void Init();

private:
	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;

	uint32_t mVertexArrayObject;
	uint32_t mVertexBufferObject;
	uint32_t mElementBufferObject;
};

