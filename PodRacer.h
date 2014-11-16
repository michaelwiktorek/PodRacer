#pragma once

#include "stdafx.h"

class PodEngine : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	PodEngine(float x, float y);
	virtual void Update(float dt);
	virtual float GetMaxThrust();

	ParticleActor *exhaust;
	float throttle;
};

class Pod : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	Pod(float x, float y);
	virtual void Update(float dt);
};

class PodRacer : public Actor
{
public:
	typedef Actor super;
	PodRacer();
	virtual void Render();
	virtual void Update(float dt);

	PodEngine *leftEngine;
	PodEngine *rightEngine;
	Pod *pod;

	float t;
};