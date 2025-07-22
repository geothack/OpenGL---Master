#include "Core/Core.h"
#include "Model.h"
#include "Core/Error.h"

Model::Model()
{
}

Model::Model(const Transform& transform) : mTransform(transform)
{
	mRigidbody = Rigidbody("rb", Transform(transform));
	//mRigidbody.GetAcceleration() = Environment::Gravity;
}

void Model::Init()
{
}

void Model::Load(const std::filesystem::path& directory, const std::filesystem::path& path)
{
	mDirectory = directory;
	Assimp::Importer import{};
	const aiScene* scene = import.ReadFile((directory.string() + "/" + path.string()).c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		auto string = "Assimp failed to load model | " + path.string() + " " + import.GetErrorString();
		Error error(string);
	}

	ProcessNode(scene->mRootNode, scene);
}

void Model::Render(Material& material, const float delta)
{
	mRigidbody.Update(delta);

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, mTransform.GetPosition());
	model = glm::translate(model, mRigidbody.GetTransform().GetPosition());
	model = glm::scale(model, mTransform.GetScale());

	if (mTransform.GetRotation() != glm::vec3(0.0))
	{
		model = glm::rotate(model, glm::radians(20.0f), mTransform.GetRotation());
	}

	material.Attach();
	material.SetMat4("Model", model);


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

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mModelMeshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<openglTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.Position = glm::vec3
		(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertex.Normals = glm::vec3
		(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0]) // Only load in the first texture
		{
			vertex.TextureCoordinates = glm::vec2
			(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.TextureCoordinates = glm::vec2(0.0f);
		}
		
		vertices.push_back(vertex);
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<openglTexture> diffuse = LoadTextures(material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuse.begin(),diffuse.end());

		std::vector<openglTexture> specular = LoadTextures(material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specular.begin(), specular.end());
	}

	return Mesh(vertices,indices,textures);
}

std::vector<openglTexture> Model::LoadTextures(aiMaterial* material, aiTextureType type)
{
	std::vector<openglTexture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString string;
		material->GetTexture(type, i, &string);
		Log::Info(string.C_Str());

		bool skip = false;

		for (unsigned int j = 0; j < mModelTextures.size(); j++)
		{
			if (std::strcmp(mModelTextures[j].GetPath().string().data(), string.C_Str()) == 0)
			{
				textures.push_back(mModelTextures[j]);
				skip = true;
			}
		}

		if (!skip)
		{
			openglTexture texture = openglTexture(mDirectory,string.C_Str(), type);
			textures.push_back(texture);
			mModelTextures.push_back(texture);
		}
	}

	return textures;
}
