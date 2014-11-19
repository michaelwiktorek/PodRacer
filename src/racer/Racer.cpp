#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

/**
 * Helper function to create a distance joint between engines.
 */
inline void bindEngines(b2DistanceJointDef &jointDef, float ay, float by, float length)
{
	jointDef.length = length;
	jointDef.localAnchorA.Set(0.5f, ay); // TODO: Do I have to make a b2Vec2 first?
	jointDef.localAnchorB.Set(-0.5f, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

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

	b2DistanceJointDef engineCouplerJointDef;
	engineCouplerJointDef.bodyA = leftEngine->GetBody();
	engineCouplerJointDef.bodyB = rightEngine->GetBody();
	engineCouplerJointDef.collideConnected = true;
	engineCouplerJointDef.frequencyHz = theTuning.GetFloat("PodSpringStrength");
	engineCouplerJointDef.dampingRatio = theTuning.GetFloat("PodSpringDamping");

	bindEngines(engineCouplerJointDef, 2.0f, -2.0f, 5.0f);
	bindEngines(engineCouplerJointDef, -2.0f, 2.0f, 5.0f);
	bindEngines(engineCouplerJointDef, 2.0f, 2.0f, 3.0f);
	bindEngines(engineCouplerJointDef, -2.0f, -2.0f, 3.0f);

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
	if (!theController.IsConnected())
	{
		return;
	}

	float leftTrigger = (theController.GetLeftTrigger() + 32768.0) / (2 * 32768.0);
	float rightTrigger = (theController.GetRightTrigger() + 32768.0) / (2 * 32768.0);
	float leftThrottle = theController.GetLeftThumbVec2().Y;
	float rightThrottle = theController.GetRightThumbVec2().Y;

	leftEngine->SetLeftFlap(leftTrigger);
	leftEngine->SetRightFlap(rightTrigger);
	rightEngine->SetLeftFlap(leftTrigger);
	rightEngine->SetRightFlap(rightTrigger);
	pod->SetLeftFlap(leftTrigger);
	pod->SetRightFlap(rightTrigger);

	leftEngine->throttle = leftThrottle;
	rightEngine->throttle = rightThrottle;
}
