#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "Render/openglUniformBuffer.h"
#include "glfwWindow.h"
#include "Render/Camera.h"

class Sphere : public Model
{
public:
	Sphere(const Transform& transform) : Model(transform)
	{
        mRigidbody = Rigidbody("rb", Transform(transform));
        //mRigidbody.GetAcceleration() = Environment::Gravity;
	}

    void Init(Material& material, Camera& camera)
    {
        Load("res/Models/Sphere", "scene.gltf");

        mCameraData.View = camera.GetViewMatrix();
        mCameraData.Projection = glm::perspective(glm::radians(45.0f), (float)glfwWindow::GetSize().Width / (float)glfwWindow::GetSize().Height, 0.1f, 100.0f);

        mUniformBuffer.CreateUBO("CameraData", sizeof(CameraData), 0);

        mUniformBuffer.UpdateUBOData("CameraData", 0, glm::value_ptr(mCameraData.Projection), sizeof(mCameraData.Projection));
        mUniformBuffer.UpdateUBOData("CameraData", sizeof(mCameraData.View), glm::value_ptr(mCameraData.View), sizeof(mCameraData.View));

        mUniformBuffer.BindUBOToShader("CameraData", material.GetHandle(), "Camera");
    }

    void Render(Material& material, Camera& camera, const float delta)
    {
        mCameraData.View = camera.GetViewMatrix();
        mCameraData.Projection = glm::perspective(glm::radians(45.0f), (float)glfwWindow::GetSize().Width / (float)glfwWindow::GetSize().Height, 0.1f, 100.0f);
        mUniformBuffer.UpdateUBOData("CameraData", 0, glm::value_ptr(mCameraData.Projection), sizeof(mCameraData.Projection));
        mUniformBuffer.UpdateUBOData("CameraData", sizeof(mCameraData.View), glm::value_ptr(mCameraData.View), sizeof(mCameraData.View));

        Model::Render(material,delta);
    }

private:
    openglUniformBuffer mUniformBuffer{};
};


class SphereArray : public ModelArray<Sphere>
{
public:

    void Init()
    {
        mModel = Sphere(Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.25f)));
        //mModel.Init();
    }
};