#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "glfwWindow.h"
#include "Render/Camera.h"

class Cube : public Model
{
public:

	Cube(const Transform& transform, Camera& camera) : Model(transform,camera)
	{
	}


	void Init(Material& material)
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

        BoundingRegion region{ glm::vec3(-1.0f),glm::vec3(1.0f) };

        GetMeshes().emplace_back(Mesh(region,Vertex::GenerateList(vertices, 36), indices));

        mUniformBuffer.BindUBOToShader("CameraData", material.GetHandle(), "Camera");
	}

    void Init(openglShader& shader)
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

        BoundingRegion region{ glm::vec3(-1.0f),glm::vec3(1.0f) };

        GetMeshes().emplace_back(Mesh(region, Vertex::GenerateList(vertices, 36), indices));

        mUniformBuffer.BindUBOToShader("CameraData", shader.GetProgram(), "Camera");
    }

    void Render(Material& material, Camera& camera, Box& box, const float delta)
    {
        Model::Render(material,camera,box,delta);
    }

    void Render(openglShader& shader, Camera& camera, Box& box, const float delta)
    {
        Model::Render(shader, camera, box, delta);
    }
    
};