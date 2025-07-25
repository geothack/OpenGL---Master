#pragma once

#include "World/Transform.h"
#include "Render/openglText.h"
#include "Render/openglSprite.h"
#include "Render/Material.h"

class Entity;

class Level
{
public:
	Level() = default;

	Entity CreateEntity(const Transform& transform);
	Entity CreateUiTextEntity(const Transform& transform, const openglText& text, const Material& material);
	Entity CreateUiTextEntity(const Transform& transform, const openglText& text, const openglShader& shader);
	Entity CreateUiSpriteEntity(const Transform& transform, const openglSprite& sprite);

	entt::registry& GetRegister() { return mRegistry; }

private:
	entt::registry mRegistry;

	friend class Entity;
};

