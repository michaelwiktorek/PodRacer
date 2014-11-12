#pragma once

#include "stdafx.h"

class PodRacer : public Actor
{
public:
	typedef Actor super;
	PodRacer();
	virtual void Render();
	virtual void Update(float dt);

	PhysicsActor *leftEngine;
	PhysicsActor *rightEngine;
	PhysicsActor *pod;

protected:
};