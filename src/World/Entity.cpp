#include "Core/Core.h"
#include "Entity.h"

Entity::Entity(entt::entity entity, Level& level) : mHandle(entity), mLevel(&level)
{
}
