#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Helper function to create a rope joint between pod and engine.
 */
inline void bindPod(b2RopeJointDef &jointDef, float ax, float ay, float bx, float by)
{
	jointDef.localAnchorA.Set(ax, ay);
	jointDef.localAnchorB.Set(bx, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

Racer::Racer(float x, float y)
{
	t = 0;

	leftEngine = new Engine(x - 2, y + 5);
	rightEngine = new Engine(x + 2, y + 5);
	pod = new Pod(x, y - 2);
	couplingStrength = 4.0;
	couplingOscillationAmount = 0.07;
	couplingOscillationRate = 17;


	SetEngineDistance(1.5);
	SetRopeLength(3.5);

	couplingBeams.push_back(CouplingBeam(
	                            Vector2(leftEngine->GetSize().X * 0.5, 1.0),
	                            Vector2(rightEngine->GetSize().X * -0.5, 1.0),
	                            2.0, Color(0.8, 0, 1)));
}

void Racer::Init()
{
	leftEngine->Init();
	rightEngine->Init();
	pod->Init();

	b2DistanceJointDef engineCouplingJointDef;
	engineCouplingJointDef.bodyA = leftEngine->GetBody();
	engineCouplingJointDef.bodyB = rightEngine->GetBody();
	engineCouplingJointDef.collideConnected = true;
	engineCouplingJointDef.frequencyHz = theTuning.GetFloat("PodSpringStrength");
	engineCouplingJointDef.dampingRatio = theTuning.GetFloat("PodSpringDamping");

	for (int i = 0; i < 4; i++)
	{
		float ay = ((i % 2 == 0) ? 1 : -1) * leftEngine->GetSize().Y * 0.45;
		float by = ((i / 2 == 0) ? 1 : -1) * rightEngine->GetSize().Y * 0.45;
		engineCouplingJointDef.length = couplingLengths[i];
		engineCouplingJointDef.localAnchorA.Set(leftEngine->GetSize().X * 0.5, ay);
		engineCouplingJointDef.localAnchorB.Set(rightEngine->GetSize().X * -0.5, by);
		engineCouplings[i] = static_cast<b2DistanceJoint *>(theWorld.GetPhysicsWorld().CreateJoint(&engineCouplingJointDef));
	}

	// TODO: Some sort of stretchy rope
	b2RopeJointDef podRopeJointDef;
	podRopeJointDef.bodyA = pod->GetBody();
	podRopeJointDef.bodyB = leftEngine->GetBody();
	podRopeJointDef.maxLength = theTuning.GetFloat("PodRopeLength");
	podRopeJointDef.collideConnected = true;

	podRopeJointDef.localAnchorA.Set(-0.75, 1.5f);
	podRopeJointDef.localAnchorB.Set(0, -2);
	leftRope = static_cast<b2RopeJoint *>(theWorld.GetPhysicsWorld().CreateJoint(&podRopeJointDef));
	podRopeJointDef.bodyB = rightEngine->GetBody();
	podRopeJointDef.localAnchorA.Set(0.75, 1.5f);
	rightRope = static_cast<b2RopeJoint *>(theWorld.GetPhysicsWorld().CreateJoint(&podRopeJointDef));

	theWorld.Add(leftEngine);
	theWorld.Add(rightEngine);
	theWorld.Add(pod);
}

void Racer::Render()
{
	float alpha = (sin(t * couplingOscillationRate * 2) + 4) / 8;

	for (CouplingBeam &couplingBeam : couplingBeams)
	{
		Color beamColor = couplingBeam.color;
		beamColor.A *= alpha;
		Vector2 leftPoint = localToWorld(leftEngine, couplingBeam.leftPosition);
		Vector2 rightPoint = localToWorld(rightEngine, couplingBeam.rightPosition);
		drawLine(leftPoint, rightPoint, beamColor, couplingBeam.width);
	}

	Color ropeColor = Color(0.1, 0.1, 0.1);
	float ropeEngineY = leftEngine->GetSize().Y * -0.4;
	float ropePodX = pod->GetSize().X * 0.3;
	float ropePodY = pod->GetSize().Y * 0.4;
	drawLine(localToWorld(leftEngine, 0, ropeEngineY), localToWorld(pod, -ropePodX, ropePodY), ropeColor, 1.0);
	drawLine(localToWorld(rightEngine, 0, ropeEngineY), localToWorld(pod, ropePodX, ropePodY), ropeColor, 1.0);
}

void Racer::Update(float dt)
{
	t += dt;

	// Make engines oscillate
	float s = 1.0 + sin(t * couplingOscillationRate) * couplingOscillationAmount;
	engineCouplings[0]->SetLength(couplingLengths[0] * s);
	engineCouplings[3]->SetLength(couplingLengths[3] * s);
	leftRope->SetMaxLength(ropeLength);
	rightRope->SetMaxLength(ropeLength);

	//
	for (int i = 0; i < 4; i++)
	{
		engineCouplings[i]->SetFrequency(couplingStrength);
	}
}

void Racer::SetCouplingStrength(float f)
{
	couplingStrength = f;
}

void Racer::SetCouplingOscillationRate(float f)
{
	couplingOscillationRate = f;
}

void Racer::SetCouplingOscillationAmount(float f)
{
	couplingOscillationAmount = f;
}

void Racer::SetEngineDistance(float d)
{
	float h = leftEngine->GetSize().Y * 0.9;
	float d2 = sqrt(h * h + d * d);
	couplingLengths[0] = d;
	couplingLengths[3] = d;
	couplingLengths[1] = d2;
	couplingLengths[2] = d2;
}

void Racer::SetRopeLength(float d)
{
	ropeLength = d;
}

void Racer::SetBaseThrust(float p)
{
	leftEngine->baseThrust = p;
	rightEngine->baseThrust = p;
}

void Racer::SetEngineSize(float width, float height)
{
	leftEngine->SetSize(width, height);
	rightEngine->SetSize(width, height);
}

void Racer::SetEngineMeterColor(Color front, Color back)
{
	leftEngine->meterColor = front;
	leftEngine->meterBackColor = back;
	rightEngine->meterColor = front;
	rightEngine->meterBackColor = back;
}

Vector2 Racer::GetVelocity()
{
	b2Vec2 vel = pod->GetBody()->GetLinearVelocity();
	return Vector2(vel.x, vel.y);
}

Vector2 Racer::GetPosition()
{
	return pod->GetPosition();
}

float Racer::GetDirection()
{
	return ((leftEngine->GetRotation() + rightEngine->GetRotation()) / 2.0) + 90;
}