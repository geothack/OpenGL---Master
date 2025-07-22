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

    void Render(Material& material, Camera& camera)
    {
        mCameraData.View = camera.GetViewMatrix();
        mUniformBuffer.UpdateUBOData("CameraData", sizeof(mCameraData.View), glm::value_ptr(mCameraData.View), sizeof(mCameraData.View));

        Model::Render(material);
    }

private:
    openglUniformBuffer mUniformBuffer{};
};