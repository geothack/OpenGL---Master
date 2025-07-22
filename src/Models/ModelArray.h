#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "Render/Material.h"
#include "Physics/3D/Rigidbody.h"

template <class T>
class ModelArray
{
public:

	void Init()
	{
		mModel.Init();
	}

	void Render(Material& material, float delta)
	{
		for (auto& rigidbody : mInstances)
		{
			rigidbody.Update(delta);
			//mModel.GetRigidbody().GetTransform().GetPosition() = rigidbody.GetTransform().GetPosition();
			mModel.GetRigidbody().GetTransform() = rigidbody.GetTransform();
			mModel.Render(material,delta);
		}
	}

	void Free()
	{
		mModel.Free();
	}


protected:
	T mModel;

private:
	std::vector<Rigidbody> mInstances;
};