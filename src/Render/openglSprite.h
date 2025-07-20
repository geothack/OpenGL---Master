#pragma once

#include "Render/Material.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"

class openglSprite
{
public:
    openglSprite() = default;
    openglSprite(Material& material);
    ~openglSprite();

    void Render(openglTexture& texture, Transform& transform);
private:
    Material mMaterial;
    uint32_t mVertexArrayObject;

    void Init();
};

