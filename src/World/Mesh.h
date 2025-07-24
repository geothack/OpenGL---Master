#pragma once

#include "Render/openglTexture.h"
#include "Render/Material.h"
#include "Algorithims/Bounds.h"
#include "Models/Box.h"
#include "Core/VertexMemory.h"

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


	void Render(Material& material, Box& box, const glm::vec3& position, const glm::vec3& scale, bool render = true);
	void Render(openglShader& shader, Box& box, const glm::vec3& position, const glm::vec3& scale, bool render = true);

	void Free();

	GLuint GetVertexArray() { return mArrayObject.val; }

	std::vector<uint32_t>& GetIndices() { return mIndices; }

private:
	void Init();

private:
	BoundingRegion mBounds;

	std::vector<Vertex> mVertices;
	std::vector<uint32_t> mIndices;
	std::vector<openglTexture> mTextures;

	ArrayObject mArrayObject;
};

