#pragma once

#include "Render/openglTexture.h"
#include "Render/Material.h"
#include "Algorithims/Bounds.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TextureCoordinates;
	glm::vec3 Normals;

	static std::vector<Vertex> GenerateList(const float* vertice, const int numVertices);
};

class Mesh
{
public:
	Mesh() = default;
	Mesh(const BoundingRegion& region, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<openglTexture>& textures = std::vector<openglTexture>{});


	void Render(Material& material, bool render = true);
	void Render(openglShader& shader, bool render = true);

	void Free() const;

	uint32_t GetVertexArray() { return mVertexArrayObject; }

	std::vector<uint32_t>& GetIndices() { return mIndices; }

private:
	void Init();

private:
	BoundingRegion mBounds;

	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;
	std::vector<openglTexture> mTextures;

	uint32_t mVertexArrayObject;
	uint32_t mVertexBufferObject;
	uint32_t mElementBufferObject;
};

