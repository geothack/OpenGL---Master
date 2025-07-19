#include "Core/Core.h"
#include "Mesh.h"

std::vector<Vertex> Vertex::GenerateList(const float* vertice, const int numVertices)
{
	std::vector<Vertex> ret(numVertices);

	int stride = sizeof(Vertex) / sizeof(float);

	for (auto i = 0; i < numVertices; i++)
	{
		ret[i].Position = glm::vec3
		(
			vertice[i * stride + 0],
			vertice[i * stride + 1],
			vertice[i * stride + 2]
		);

		ret[i].TextureCoordinates = glm::vec2
		(
			vertice[i * stride + 3],
			vertice[i * stride + 4]
		);
	}

	return ret;
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<openglTexture>& textures) : mVertices(vertices)
	, mIndices(indices), mMeshTextures(textures)
{
	Init();
}

void Mesh::Render(openglShader& shader)
{
	for (uint32_t i = 0; i < mMeshTextures.size(); i++)
	{
		shader.SetInt(mMeshTextures[i].GetName(), i);
		//glActiveTexture(GL_TEXTURE0 + i);
		mMeshTextures[i].Attach();
		glBindTextureUnit(i, mMeshTextures[i].GetHandle());
	}

	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Free()
{
	glDeleteVertexArrays(1, &mVertexArrayObject);
	glDeleteBuffers(1, &mVertexBufferObject);
	glDeleteBuffers(1, &mElementBufferObject);

}

void Mesh::Init()
{
	glGenVertexArrays(1, &mVertexArrayObject);
	glGenBuffers(1, &mVertexBufferObject);
	glGenBuffers(1, &mElementBufferObject);

	glBindVertexArray(mVertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32_t), &mIndices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex,TextureCoordinates)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
