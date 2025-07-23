#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "Render/Material.h"
#include "Render/openglUniformBuffer.h"
#include "glfwWindow.h"
#include "Render/Camera.h"

class Plane : public Model
{
public:
    Plane(const Transform& transform) : Model(transform)
    {
        //Init();
        mRigidbody = Rigidbody("rb", Transform(transform));
        //mRigidbody.GetAcceleration() = Environment::Gravity;
    }


    void Init(Material& material, Camera& camera)
    {
        float vertices[] = 
        {
            // positions            // texcoords  // normals
             25.0f, -0.5f,  25.0f,  25.0f,  0.0f, 0.0f, 1.0f, 0.0f,
            -25.0f, -0.5f,  25.0f,   0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
            -25.0f, -0.5f, -25.0f,   0.0f, 25.0f, 0.0f, 1.0f, 0.0f,

             25.0f, -0.5f,  25.0f,  25.0f,  0.0f, 0.0f, 1.0f, 0.0f,
            -25.0f, -0.5f, -25.0f,   0.0f, 25.0f, 0.0f, 1.0f, 0.0f,
             25.0f, -0.5f, -25.0f,  25.0f, 25.0f, 0.0f, 1.0f, 0.0f,
        };

        std::vector<uint32_t> indices(6);

        for (uint32_t i = 0; i < 6; i++)
        {
            indices[i] = i;
        }

        BoundingRegion region{ glm::vec3(-25.0f, -0.5f,  -25.0f),glm::vec3(25.0f, 0.5f,  25.0f) };

        GetMeshes().emplace_back(Mesh(region,Vertex::GenerateList(vertices, 6), indices));

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

        //glm::mat4 model = glm::mat4(1.0);
        //model = glm::translate(model, mTransform.GetPosition());
        //model = glm::scale(model, mTransform.GetScale());
        ////model = glm::rotate(model, glm::radians(20.0f), mTransform.GetRotation());

        //material.Attach();
        //material.SetMat4("Model", model);

        Model::Render(material,delta);
    }

private:
    openglUniformBuffer mUniformBuffer{};
};