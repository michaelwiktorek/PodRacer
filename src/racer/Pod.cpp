#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Create a new pod at (x, y).
 */
Pod::Pod(float x, float y)
{
	super();
	SetSize(2.0f, 3.0f);
	SetColor(0.3f, 0.3f, 0.7f);
	SetPosition(x, y);
	SetRestitution(0.1f);
	SetFriction(0.3f);
	InitPhysics();

	leftFlap = 0;
	rightFlap = 0;
}

/**
 * Update the pod.
 */
void Pod::Update(float dt)
{
	applyAerodynamics(this, theTuning.GetFloat("PodDrag"));

	b2Vec2 leftStart = b2Vec2(-0.5, 0);
	b2Vec2 leftEnd = leftStart + b2Vec2(-1, 0);
	applyAerodynamicsToEdge(this, leftStart, leftEnd, theTuning.GetFloat("FlapDrag") * leftFlap, 0.0);
	b2Vec2 rightStart = b2Vec2(0.5, 0);
	b2Vec2 rightEnd = rightStart + b2Vec2(1, 0);
	applyAerodynamicsToEdge(this, rightEnd, rightStart, theTuning.GetFloat("FlapDrag") * rightFlap, 0.0);
}

/**
 * Draw the pod and it's flaps.
 */
void Pod::Render()
{
	super::Render();

	Vector2 leftStart = Vector2(-1.0, 0);
	Vector2 leftEnd = leftStart + Vector2(-sin(leftFlap), cos(leftFlap)) * 0.8;
	drawLine(localToWorld(this, leftStart), localToWorld(this, leftEnd), Color(0, 0, 0), 1);
	Vector2 rightStart = Vector2(1.0, 0);
	Vector2 rightEnd = rightStart + Vector2(sin(rightFlap), cos(rightFlap)) * 0.8;
	drawLine(localToWorld(this, rightStart), localToWorld(this, rightEnd), Color(0, 0, 0), 1);
}

void Pod::SetLeftFlap(float x)
{
	leftFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}

void Pod::SetRightFlap(float x)
{
	rightFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}