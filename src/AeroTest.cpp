#include "AeroTest.h"
#include <physics/Aerodynamics.h>
#include <math.h>

AeroTest::AeroTest()
{
	SetSize(1.0, 5.0);
	SetColor(0.3, 0.3f, 0.3);
	SetPosition(0, 0);
	InitPhysics();
}

void AeroTest::Update(float dt)
{
	if (!theController.IsConnected())
	{
		return;
	}

	float throttle = theController.GetLeftThumbVec2().Y;
	if (throttle > 0)
	{
		Vector2 thrust = Vector2(0, throttle * 500);
		Vector2 point = Vector2(0, 0);
		ApplyLocalForce(thrust, point);
	}

	float torque = theController.GetRightThumbVec2().X * -100;

	GetBody()->ApplyTorque(torque);

	applyAerodynamics(this, 1.0);
}
