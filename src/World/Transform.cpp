#include "Core/Core.h"
#include "Transform.h"

Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : mPosition(position), mRotation(rotation), mScale(scale)
{
}

Transform::Transform(const Transform& transform) : mPosition(transform.mPosition), mRotation(transform.mRotation), mScale(transform.mScale)
{
}

Transform::~Transform()
{
}
