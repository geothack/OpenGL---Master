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

Mesh::Mesh(const BoundingRegion& region, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<openglTexture>& textures) : mVertices(vertices)
, mIndices(indices), mTextures(textures), mBounds(region)
{
	Init();
}

void Mesh::Render(Material& material, Box& box, const glm::vec3& position, const glm::vec3& scale, bool render)
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

	if (render)
	{
		box.AddInstance(mBounds, position, scale);

		mArrayObject.Attach();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
		ArrayObject::Detach();

		glActiveTexture(GL_TEXTURE0);
	}
}

void Mesh::Render(openglShader& shader, Box& box, const glm::vec3& position, const glm::vec3& scale, bool render)
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

	if (render)
	{
		box.AddInstance(mBounds, position, scale);

		mArrayObject.Attach();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mIndices.size()), GL_UNSIGNED_INT, 0);
		ArrayObject::Detach();

		glActiveTexture(GL_TEXTURE0);
	}

}

void Mesh::Free() 
{
	mArrayObject.Free();
}

void Mesh::Init()
{
	mArrayObject.Generate();
	mArrayObject.Attach();

	mArrayObject["EBO"] = BufferObject(GL_ELEMENT_ARRAY_BUFFER);
	mArrayObject["EBO"].Generate();
	mArrayObject["EBO"].Attach();
	mArrayObject["EBO"].SetData<uint32_t>(mIndices.size(),&mIndices[0],GL_STATIC_DRAW);


	mArrayObject["VBO"] = BufferObject(GL_ARRAY_BUFFER);
	mArrayObject["VBO"].Generate();
	mArrayObject["VBO"].Attach();
	mArrayObject["VBO"].SetData<Vertex>(mVertices.size(), &mVertices[0], GL_STATIC_DRAW);


	mArrayObject["VBO"].SetAttPointer<GLfloat>(0, 3, GL_FLOAT, 8, 0);
	mArrayObject["VBO"].SetAttPointer<GLfloat>(1, 2, GL_FLOAT, 8, 3);
	mArrayObject["VBO"].SetAttPointer<GLfloat>(2, 3, GL_FLOAT, 8, 5);


	ArrayObject::Detach();
}
