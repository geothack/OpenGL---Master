#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "Render/Material.h"
#include "Physics/3D/Rigidbody.h"
#include "Render/Camera.h"

template <class T>
class ModelArray
{
public:

	void Init(Material& material, Camera& camera)
	{
		mModel.Init(material, camera);

		glGenBuffers(1, &mPositionVertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, mPositionVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &mScaleVertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		for (unsigned int i = 0, size = mModel.GetMeshes().size(); i < size; i++)
		{
			glBindVertexArray(mModel.GetMeshes()[i].GetVertexArray());

			glBindBuffer(GL_ARRAY_BUFFER, mPositionVertexBufferObject);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
			glEnableVertexAttribArray(3);

			glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
			glEnableVertexAttribArray(4);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glVertexAttribDivisor(3, 1); // Reset third attrib every 1 instance
			glVertexAttribDivisor(4, 1);

			glBindVertexArray(0);
		}
	}

	void Render(Material& material, float delta, bool setLists = true, bool render = true)
	{
		if (setLists)
		{
			mTransforms.clear();

			for (auto& rigidbody : mInstances)
			{
				rigidbody.Update(delta);
				mTransforms.emplace_back(rigidbody.GetTransform());
			}
		}

		material.Attach();
		material.SetMat4("Model", glm::mat4(1.0));

		mModel.Render(material, delta, false, false);

		auto size = std::min(100, static_cast<int>(mTransforms.size()));

		if (mTransforms.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mPositionVertexBufferObject);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetPosition());

			glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetScale());

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (render)
		{
			for (unsigned int i = 0, length = mModel.GetMeshes().size(); i < length; i++)
			{
				glBindVertexArray(mModel.GetMeshes()[i].GetVertexArray());

				glDrawElementsInstanced(GL_TRIANGLES, mModel.GetMeshes()[i].GetIndices().size(), GL_UNSIGNED_INT, 0, size);

				glBindVertexArray(0);
			}
		}
	}

	void Render(openglShader& shader, float delta, bool setLists = true, bool render = true)
	{
		if (setLists)
		{
			mTransforms.clear();

			for (auto& rigidbody : mInstances)
			{
				rigidbody.Update(delta);
				mTransforms.emplace_back(rigidbody.GetTransform());
			}
		}

		shader.Attach();
		shader.SetMat4("Model",glm::mat4(1.0));

		mModel.Render(shader, delta, false);

		auto size = std::min(100, static_cast<int>(mTransforms.size()));

		if (mTransforms.size() != 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mPositionVertexBufferObject);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetPosition());

			glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetScale());

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (render)
		{
			for (unsigned int i = 0, length = mModel.GetMeshes().size(); i < length; i++)
			{
				glBindVertexArray(mModel.GetMeshes()[i].GetVertexArray());

				glDrawElementsInstanced(GL_TRIANGLES, mModel.GetMeshes()[i].GetIndices().size(), GL_UNSIGNED_INT, 0, size);

				glBindVertexArray(0);
			}
		}
	}

	void Free()
	{
		mModel.Free();
	}


protected:
	T mModel;

	uint32_t mPositionVertexBufferObject;
	uint32_t mScaleVertexBufferObject;
	std::vector<Transform> mTransforms;

private:
	std::vector<Rigidbody> mInstances;
};