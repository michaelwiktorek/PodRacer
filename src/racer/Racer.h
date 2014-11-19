#pragma once

#include "stdafx.h"

/**
 * The engine of a pod racer. Has flaps to steer.
 */
class Engine : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	Engine(float x, float y);
	virtual void Update(float dt);
	virtual void Render();
	virtual void SetLeftFlap(float x);
	virtual void SetRightFlap(float x);
	virtual float GetMaxThrust();

	ParticleActor *exhaust;
	float throttle;
	float leftFlap;
	float rightFlap;
};

/**
 * The pod where the pilot sits.
 */
class Pod : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	Pod(float x, float y);
	virtual void Update(float dt);
	virtual void Render();
	virtual void SetLeftFlap(float x);
	virtual void SetRightFlap(float x);

	float leftFlap;
	float rightFlap;
};

/**
 * The owner of the two engines and a pod.
 */
class Racer : public Actor
{
public:
	typedef Actor super;
	Racer();
	virtual void Render();
	virtual void Update(float dt);

	Engine *leftEngine;
	Engine *rightEngine;
	Pod *pod;

	float t;
};