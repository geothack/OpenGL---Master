#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "World/Transform.h"

class Cube : public Model
{
public:

	Cube(const Transform& transform) : mTransform(transform)
	{
        Init();
	}


	void Init()
	{
        float vertices[] =
        {
            -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f,  0.0f, -1.0f, 
             1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
             1.0f, -1.0f, -1.0f,    1.0f, 0.0f,   0.0f,  0.0f, -1.0f,     
             1.0f,  1.0f, -1.0f,    1.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
            -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   0.0f,  0.0f, -1.0f, 
            -1.0f,  1.0f, -1.0f,    0.0f, 1.0f,   0.0f,  0.0f, -1.0f, 
            // front face                      
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f, 
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f,  0.0f,  1.0f, 
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f, 
             1.0f,  1.0f,  1.0f,   1.0f, 1.0f,    0.0f,  0.0f,  1.0f, 
            -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,    0.0f,  0.0f,  1.0f, 
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f,  0.0f,  1.0f, 
            // left face                       
            -1.0f,  1.0f,  1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f, -1.0f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
            // right face                      
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    1.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f,    1.0f,  0.0f,  0.0f,
             1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    1.0f,  0.0f,  0.0f,
            // bottom face                     
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
             1.0f, -1.0f, -1.0f,   1.0f, 1.0f,    0.0f, -1.0f,  0.0f,
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
             1.0f, -1.0f,  1.0f,   1.0f, 0.0f,    0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,    0.0f, -1.0f,  0.0f,
            -1.0f, -1.0f, -1.0f,   0.0f, 1.0f,    0.0f, -1.0f,  0.0f,
            // top face                        
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
             1.0f,  1.0f , 1.0f,   1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
             1.0f,  1.0f, -1.0f,   1.0f, 1.0f,     0.0f,  1.0f,  0.0f,
             1.0f,  1.0f,  1.0f,   1.0f, 0.0f,     0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,     0.0f,  1.0f,  0.0f,
            -1.0f,  1.0f,  1.0f,   0.0f, 0.0f,     0.0f,  1.0f,  0.0f
        };

        std::vector<uint32_t> indices(36);

        for (uint32_t i = 0; i < 36; i++)
        {
            indices[i] = i;
        }

        GetMeshes().emplace_back(Mesh(Vertex::GenerateList(vertices, 36), indices));
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