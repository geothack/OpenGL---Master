#pragma once

#include "Physics/2D/PhysicsWorld2D.h"

struct BodyShape
{
	float X = 0;
	float Y = 0;
	float Width = 50;
	float Height = 50;
	float Gravity = 1.0f;

	b2BodyType Type = b2_dynamicBody;
	bool FixedRotation = true;
	bool CanSleep = true;
	bool Enabled = true;
};

class PhysicsBody2D
{
public:
	PhysicsBody2D(PhysicsWorld2D& world, const BodyShape& body);

	void Destroy();

	void Sleep(bool set);

	inline b2BodyDef& GetBodyDef() { return mBodyDef; }
	inline const b2BodyId& const GetBodyId() const { return mBodyId; }
	inline const float GetWidth() const { return mBody.Width; }
	inline const float GetHeight() const { return mBody.Height; }

private:
	b2BodyDef mBodyDef = b2DefaultBodyDef();
	b2BodyId mBodyId;

	BodyShape mBody;
	PhysicsWorld2D& mWorld;
};

