#pragma once

#include <stdafx.h>

class PodEngine : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	PodEngine(float x, float y);
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

class PodRacer : public Actor
{
public:
	typedef Actor super;
	PodRacer();
	virtual void Render();
	virtual void Update(float dt);
	void UpdateHUD();

	PodEngine *leftEngine;
	PodEngine *rightEngine;
	Pod *pod;

	float t;
};