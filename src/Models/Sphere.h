#pragma once

#include "Core/Core.h"

#include "Render/Model.h"
#include "Render/openglUniformBuffer.h"
#include "glfwWindow.h"
#include "Render/Camera.h"

class Sphere : public Model
{
public:
	Sphere(const Transform& transform, Camera& camera) : Model(transform,camera,BoundTypes::SPHERE)
	{
	}

    void Init(Material& material)
    {
        Load("res/Models/Sphere", "scene.gltf");

        mUniformBuffer.BindUBOToShader("CameraData", material.GetHandle(), "Camera");
    }

    void Render(Material& material, Camera& camera, Box& box, const float delta)
    {
        Model::Render(material,camera,box,delta);
    }

};

