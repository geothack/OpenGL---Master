#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "World/Transform.h"
#include "Render/Material.h"

class Plane : public Model
{
public:
    Plane(const Transform& transform) : mTransform(transform)
    {
        Init();
    }


    void Init()
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

        GetMeshes().emplace_back(Mesh(Vertex::GenerateList(vertices, 6), indices));
    }

    void Render(Material& material)
    {
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, mTransform.GetPosition());
        model = glm::scale(model, mTransform.GetScale());
        model = glm::rotate(model, glm::radians(20.0f), mTransform.GetRotation());

        material.Attach();
        material.SetMat4("Model", model);

        Model::Render(material);
    }

private:
    Transform mTransform;
};