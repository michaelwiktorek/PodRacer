#pragma once

#include <stdafx.h>

class AeroTest : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	AeroTest();
	virtual void Update(float dt);
};