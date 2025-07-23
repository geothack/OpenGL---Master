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

		ret[i].Normals = glm::vec3
		(
			vertice[i * stride + 5],
			vertice[i * stride + 6],
			vertice[i * stride + 7]
		);
	}

	return ret;
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<openglTexture>& textures) : mVertices(vertices)
	, mIndices(indices), mTextures(textures)
{
	Init();
}

void Mesh::Render(Material& material)
{
	if (mTextures.size() >= 1)
	{
		uint32_t diffuse = 0;
		uint32_t specular = 0;

		for (size_t i = 0; i < mTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string name;
			switch (mTextures[i].GetType())
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuse++);
				break;

			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specular++);
				break;
			}

			material.SetInt(name, i);
			mTextures[i].Attach();
		}
	}
	else
	{
		material.AttachTextures();
	}

	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Render(openglShader& shader)
{
	if (mTextures.size() >= 1)
	{
		uint32_t diffuse = 0;
		uint32_t specular = 0;

		for (size_t i = 0; i < mTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string name;
			switch (mTextures[i].GetType())
			{
			case aiTextureType_DIFFUSE:
				name = "diffuse" + std::to_string(diffuse++);
				break;

			case aiTextureType_SPECULAR:
				name = "specular" + std::to_string(specular++);
				break;
			}

			shader.SetInt(name, i);
			mTextures[i].Attach();
		}
	}
	else
	{
		//shader.AttachTextures();
	}

	glBindVertexArray(mVertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Free() const
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

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normals)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
