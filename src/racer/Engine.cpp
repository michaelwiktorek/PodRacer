#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Create a new engine at (x, y).
 */
Engine::Engine(float x, float y)
{
	super();
	SetSize(1.0, 5.0);
	SetColor(0.3, 0.3, 0.3);
	SetPosition(x, y);
	SetRestitution(0.1);
	SetFriction(0.2);
	InitPhysics();

	leftFlap = 0;
	rightFlap = 0;

	// Particle emmitter
	throttle = 0;
	exhaust = new ParticleActor();
	exhaust->SetColor(1.0, 0.2, 0, 0.8);
	exhaust->SetEndColor(Color(1.0f, 1.0f, 0, 0));
	exhaust->SetDrawShape(ADS_Circle);
	exhaust->SetSize(Vector2(0.3, 0.3));
	exhaust->SetEndScale(0.5);
	exhaust->SetMaxParticles(1800);
	exhaust->SetParticlesPerSecond(0.0f);
	exhaust->SetParticleLifetime(0.15f);
	exhaust->SetGravity(Vector2::Zero);
	exhaust->SetSpeedRange(0, 2);
	exhaust->SetSpread(MathUtil::Pi);
	theWorld.Add(exhaust); // TODO: Add at a different time that construction
}

void Engine::SetLeftFlap(float x)
{
	leftFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}

void Engine::SetRightFlap(float x)
{
	rightFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}

/**
 * @return The maximum amount of thrust this engine can produce in its current state.
 */
float Engine::GetMaxThrust()
{
	float result = theTuning.GetFloat("EnginePower");
	result += GetBody()->GetLinearVelocity().Length() * 0.001 * result;
	return result;
}

/**
 * Updates the engine.
 */
void Engine::Update(float dt)
{
	exhaust->SetPosition(localToWorld(this, 0, -2.5));

	float size = throttle * 0.4 + 0.2;
	exhaust->SetSize(Vector2(size, size));
	exhaust->SetParticlesPerSecond(60.0f * throttle + 60);
	exhaust->SetSpeedRange(0, 5 * throttle + 2);

	// Physics
	applyAerodynamics(this, theTuning.GetFloat("EngineDrag"));
	b2Vec2 leftStart = b2Vec2(-0.5, 1);
	b2Vec2 leftEnd = leftStart + b2Vec2(-1, 0);
	applyAerodynamicsToEdge(this, leftStart, leftEnd, theTuning.GetFloat("FlapDrag") * leftFlap, 0.0);
	b2Vec2 rightStart = b2Vec2(0.5, 1);
	b2Vec2 rightEnd = rightStart + b2Vec2(1, 0);
	applyAerodynamicsToEdge(this, rightEnd, rightStart, theTuning.GetFloat("FlapDrag") * rightFlap, 0.0);
	if (throttle > 0.01)
	{
		Vector2 thrust = Vector2(0, throttle * GetMaxThrust());
		Vector2 point = Vector2(0, 0); // TODO: Don't apply thrust to center
		ApplyLocalForce(thrust, point);
	}
}

void Engine::Render()
{
	super::Render();
	float drawPoint = std::max(3.6*throttle-1.8, -1.8);
	drawLine(localToWorld(this, 0, drawPoint), localToWorld(this, 0, -1.8), Color(0, 1, 1), 1);

	Vector2 leftStart = Vector2(-0.5, 1);
	Vector2 leftEnd = leftStart + Vector2(-sin(leftFlap), cos(leftFlap)) * 0.8;
	drawLine(localToWorld(this, leftStart), localToWorld(this, leftEnd), Color(0, 0, 0), 1);
	Vector2 rightStart = Vector2(0.5, 1);
	Vector2 rightEnd = rightStart + Vector2(sin(rightFlap), cos(rightFlap)) * 0.8;
	drawLine(localToWorld(this, rightStart), localToWorld(this, rightEnd), Color(0, 0, 0), 1);
}