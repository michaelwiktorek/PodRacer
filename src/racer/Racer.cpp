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


Racer::Racer()
{
	super();
	t = 0;

	leftEngine = new Engine(-2, 5);
	rightEngine = new Engine(2, 5);
	pod = new Pod(0, -2);

	b2DistanceJointDef engineCouplingJointDef;
	engineCouplingJointDef.bodyA = leftEngine->GetBody();
	engineCouplingJointDef.bodyB = rightEngine->GetBody();
	engineCouplingJointDef.collideConnected = true;
	engineCouplingJointDef.frequencyHz = theTuning.GetFloat("PodSpringStrength");
	engineCouplingJointDef.dampingRatio = theTuning.GetFloat("PodSpringDamping");

	engineCouplingLengths[0] = 3;
	engineCouplingLengths[1] = 5;
	engineCouplingLengths[2] = 5;
	engineCouplingLengths[3] = 3;

	for (int i = 0; i < 4; i++)
	{
		float ay = (i % 2 == 0) ? 2 : -2;
		float by = (i / 2 == 0) ? 2 : -2;
		engineCouplingJointDef.length = engineCouplingLengths[i];
		engineCouplingJointDef.localAnchorA.Set(0.5f, ay);
		engineCouplingJointDef.localAnchorB.Set(-0.5f, by);
		engineCouplings[i] = static_cast<b2DistanceJoint *>(theWorld.GetPhysicsWorld().CreateJoint(&engineCouplingJointDef));
	}

	// TODO: Some sort of stretchy rope
	b2RopeJointDef podRopeJointDef;
	podRopeJointDef.bodyA = pod->GetBody();
	podRopeJointDef.bodyB = leftEngine->GetBody();
	podRopeJointDef.maxLength = theTuning.GetFloat("PodRopeLength");
	podRopeJointDef.collideConnected = true;

	bindPod(podRopeJointDef, -0.75f, 1.5f, 0, -2.0f);
	podRopeJointDef.bodyB = rightEngine->GetBody();
	bindPod(podRopeJointDef, 0.75f, 1.5f, 0, -2.0f);

	// TODO: These should be added when the Pod Racer is added to the world, not when it is instantiated.
	theWorld.Add(leftEngine);
	theWorld.Add(rightEngine);
	theWorld.Add(pod);
}

void Racer::Render()
{
	Color beamColor = Color(0.8, 0, 1, (sin(t * 40) + 4) / 8);
	drawLine(localToWorld(leftEngine, 0.5, 1), localToWorld(rightEngine, -0.5, 1), beamColor, 2.2);
	Color ropeColor = Color(0.1, 0.1, 0.1);
	drawLine(localToWorld(leftEngine, 0, -2), localToWorld(pod, -0.75, 1.5), ropeColor, 1.0);
	drawLine(localToWorld(rightEngine, 0, -2), localToWorld(pod, 0.75, 1.5), ropeColor, 1.0);
}

void Racer::Update(float dt)
{
	t += dt;

	// Make engines oscillate
	float s = sin(t * 17) * 0.07;
	engineCouplings[1]->SetLength(engineCouplingLengths[1] + s);
	engineCouplings[2]->SetLength(engineCouplingLengths[2] + s);
}
