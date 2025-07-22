#pragma once

#include "World/Level.h"

class PhysicsWorld2D
{
public:
	PhysicsWorld2D(Level& level);
	~PhysicsWorld2D();

	void Update(float timeStep);

	inline b2WorldId& GetId() { return mWorldId; }

private:
	b2WorldDef mWorldDef = b2DefaultWorldDef();
	b2WorldId mWorldId;

	Level& mActiveLevel;
};

