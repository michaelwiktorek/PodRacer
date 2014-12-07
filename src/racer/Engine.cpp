#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Create a new engine at (x, y).
 */
Engine::Engine(float x, float y)
{
	SetSize(0.5, 2.5);
	SetColor(0.3, 0.3, 0.3);
	SetPosition(x, y);
	SetRestitution(0.1);
	SetFriction(0.2);

	baseThrust = 1.0;
	meterWidth = 1.0;
	meterBackColor = Color(0.4, 0.4, 0.4);
	meterColor = Color(0, 1, 1);

	// Particle emmitter
	throttle = 0;
	exhaust = new ParticleActor();
	exhaust->SetColor(1.0, 0.2, 0, 0.8);
	exhaust->SetEndColor(Color(1.0f, 1.0f, 0, 0));
	exhaust->SetDrawShape(ADS_Circle);
	exhaust->SetSize(Vector2(0.3, 0.3));
	exhaust->SetEndScale(0.5);
	exhaust->SetMaxParticles(1800);
	exhaust->SetParticlesPerSecond(60.0f);
	exhaust->SetParticleLifetime(0.15f);
	exhaust->SetGravity(Vector2::Zero);
	exhaust->SetSpeedRange(0, 2);
	exhaust->SetSpread(0);
}

void Engine::Init()
{
	InitPhysics();
}

/**
 * Updates the engine.
 */
void Engine::Update(float dt)
{
	// Physics
	applyAerodynamics(this, theTuning.GetFloat("EngineDrag"));

	for (Flap &flap : flaps)
	{
		flap.Update(this);
	}

	if (throttle > 0.01)
	{
		Vector2 thrust = Vector2(0, throttle * GetMaxThrust());
		Vector2 point = Vector2(0, 0); // TODO: Don't apply thrust to center
		ApplyLocalForce(thrust, point);
	}
	// exhaust->Update(dt);
}

void Engine::Render()
{
	// Exhaust
	float size = (throttle * 0.4 + 0.25) * GetSize().X;
	exhaust->SetSize(Vector2(size, size));
	float speed = 12 - GetBody()->GetLinearVelocity().Length() * 0.7;
	exhaust->SetSpeedRange(speed, speed);
	exhaust->SetRotation(GetRotation() - 90);
	exhaust->SetPosition(localToWorld(this, 0, -GetSize().Y * 0.5));
	exhaust->Update(1 / 60.0);
	exhaust->Render();

	// Body
	super::Render();

	// Meter thing
	float height = GetSize().Y;
	float meterLength = 0.75 * height;
	Vector2 meterStart = localToWorld(this, 0, -meterLength * 0.5);
	Vector2 meterEnd = localToWorld(this, 0, -meterLength * 0.5 + meterLength * throttle);
	Vector2 meterBackEnd = localToWorld(this, 0, meterLength * 0.5);
	drawLine(meterStart, meterBackEnd, meterBackColor, meterWidth);
	drawLine(meterStart, meterEnd, meterColor, meterWidth);

	// Flaps
	for (Flap &flap : flaps)
	{
		flap.Render(this);
	}
}

void Engine::SetThrottle(float x)
{
	throttle = MathUtil::Clamp(x, 0.0f, 1.0f);
}

float Engine::GetMaxThrust()
{
	float result = theTuning.GetFloat("EnginePower") * baseThrust;
	result += GetBody()->GetLinearVelocity().Length() * 0.001 * result;
	return result;
}

void Engine::SetLeftFlap(float x)
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

void Engine::SetRightFlap(float x)
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

void Engine::AddFlap(Flap flap)
{
	flaps.push_back(flap);
}