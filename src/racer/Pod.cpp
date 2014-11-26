#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Create a new pod at (x, y).
 */
Pod::Pod(float x, float y)
{
	super();
	SetSize(1.0, 1.5);
	SetColor(0.3f, 0.3f, 0.7f);
	SetPosition(x, y);
	SetRestitution(0.1f);
	SetFriction(0.3f);
}

void Pod::Init()
{
	InitPhysics();
	GetBody()->SetAngularDamping(2.5);
}

/**
 * Update the pod.
 */
void Pod::Update(float dt)
{
	applyAerodynamics(this, theTuning.GetFloat("PodDrag"));

	for (Flap &flap : flaps)
	{
		flap.Update(this);
	}
}

/**
 * Draw the pod and it's flaps.
 */
void Pod::Render()
{
	// Body
	super::Render();

	// Flaps
	for (Flap &flap : flaps)
	{
		flap.Render(this);
	}
}

void Pod::SetLeftFlap(float x)
{
	x = MathUtil::Clamp(x, 0.0f, 1.0f);
	for (Flap &flap : flaps)
	{
		if (flap.side == Flap::LEFT)
		{
			flap.activation = x;
		}
	}
}

void Pod::SetRightFlap(float x)
{
	x = MathUtil::Clamp(x, 0.0f, 1.0f);
	for (Flap &flap : flaps)
	{
		if (flap.side == Flap::RIGHT)
		{
			flap.activation = x;
		}
	}
}

void Pod::AddFlap(Flap flap)
{
	flaps.push_back(flap);
}