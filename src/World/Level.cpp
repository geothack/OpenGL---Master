#include "Core/Core.h"
#include "Level.h"
#include "World/Entity.h"

Entity Level::CreateEntity(const Transform& transform)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	return entity;
}

Entity Level::CreateUiTextEntity(const Transform& transform, const openglText& text, const Material& material)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	entity.AddComponent<openglText>(text);
	entity.AddComponent<Material>(material);
	return entity;
}

Entity Level::CreateUiTextEntity(const Transform& transform, const openglText& text, const openglShader& shader)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	entity.AddComponent<openglText>(text);
	entity.AddComponent<openglShader>(shader);
	return entity;
}

Entity Level::CreateUiSpriteEntity(const Transform& transform, const openglSprite& sprite)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	entity.AddComponent<openglSprite>(sprite);
	return entity;
}
