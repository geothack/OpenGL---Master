#pragma once

#include "Render/openglShader.h"
#include "Render/openglTexture.h"
#include "World/Transform.h"

class openglSprite
{
public:
    openglSprite() = default;
    openglSprite(openglShader& shader);
    ~openglSprite();

    void Render(openglTexture& texture, Transform& transform);
private:
    openglShader mShader;
    uint32_t mVertexArrayObject;

    void Init();
};

