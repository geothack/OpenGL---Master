#include "Core\Core.h"
#include "PhysicsBody2D.h"

PhysicsBody2D::PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body) : mWorld(world), mBody(body)
{
	mBodyDef.type = mBody.Type;
    mBodyDef.position = b2Vec2(mBody.X, mBody.Y);
    mBodyDef.fixedRotation = mBody.FixedRotation;
    mBodyDef.enableSleep = mBody.CanSleep;
    mBodyDef.gravityScale = mBody.Gravity;
    mBodyDef.isEnabled = mBody.Enabled;
    //mBodyDef.linearDamping = 0.0f;
    //mBodyDef.angularDamping = 0.01f;
    mBodyId = b2CreateBody(mWorld.GetId(), &mBodyDef);

    b2Polygon dynamicBox = b2MakeBox(mBody.Width, mBody.Height);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;

    b2CreatePolygonShape(mBodyId, &shapeDef, &dynamicBox);
}

void PhysicsBody2D::Destroy()
{
    b2DestroyBody(mBodyId);
}

void PhysicsBody2D::Sleep(bool set)
{
    b2Body_SetAwake(mBodyId, set);
}
