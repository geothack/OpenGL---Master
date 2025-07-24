#pragma once

#include "Render/Material.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"
#include "openglUniformBuffer.h"
#include "Core/VertexMemory.h"

class openglSprite
{
public:
    openglSprite() = default;
    ~openglSprite();

    void Render(Material& material, Transform& transform, const openglTexture& texture = openglTexture{});

    void Init(Material& material);

private:
    ArrayObject mArrayObject;

    struct SpriteCamera
    {
        alignas(16) glm::mat4 Projection;
    };

    SpriteCamera mSpriteCamera;

    openglUniformBuffer mUniformBuffer{};
};

