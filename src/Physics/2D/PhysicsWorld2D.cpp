#include "Core\Core.h"
#include "PhysicsWorld2D.h"
#include "Physics/2D/PhysicsBody2D.h"
#include "World/Transform.h"

PhysicsWorld2D::PhysicsWorld2D(Level& level) : mActiveLevel(level)
{
    mWorldDef.gravity = b2Vec2(0.0f, 10.0f);

    mWorldId = b2CreateWorld(&mWorldDef);
}

PhysicsWorld2D::~PhysicsWorld2D()
{
    b2DestroyWorld(mWorldId);
}

void PhysicsWorld2D::Update(float timeStep)
{
    b2World_Step(mWorldId, timeStep, 4);

    /*for (auto& entity : mActiveLevel->GetHandle().view<entt::entity>())
    {
        if (mActiveLevel->GetHandle().any_of<PhysicsBody2D>(entity))
        {
            b2Vec2 position = b2Body_GetPosition(mActiveLevel->GetHandle().get<PhysicsBody2D>(entity).GetBodyId());

            mActiveLevel->GetHandle().get<Transform>(entity).UpdatePosition(glm::vec2(position.x, position.y));
        }
    }*/
}
