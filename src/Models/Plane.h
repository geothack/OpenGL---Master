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
    Plane(const Transform& transform, Camera& camera) : Model(transform,camera)
    {
    }


    void Init(Material& material)
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

        mUniformBuffer.BindUBOToShader("CameraData", material.GetHandle(), "Camera");
    }

    void Render(Material& material, Camera& camera, Box& box, const float delta)
    {
        Model::Render(material,camera,box,delta);
    }

};