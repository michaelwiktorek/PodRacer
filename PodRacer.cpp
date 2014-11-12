#include "PodRacer.h"

PhysicsActor *makeEngine(int x, int y)
{
	PhysicsActor *engine = new PhysicsActor();
	engine->SetPosition(x, y);
	engine->SetSize(1.0f, 5.0f);
	engine->SetColor(0.3f, 0.3f, 0.3f);
	engine->InitPhysics();
	return engine;
}

void bindEngines(b2DistanceJointDef &jointDef, float ay, float by, float length)
{
	jointDef.length = length;
	jointDef.localAnchorA.Set(0.5f, ay); // TODO: Do I have to make a b2Vec2 first?
	jointDef.localAnchorB.Set(-0.5f, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

void bindPod(b2RopeJointDef &jointDef, float ax, float ay, float bx, float by)
{
	jointDef.localAnchorA.Set(ax, ay); // TODO: Do I have to make a b2Vec2 first?
	jointDef.localAnchorB.Set(bx, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

PhysicsActor *makePod(int x, int y)
{
	PhysicsActor *pod = new PhysicsActor();
	pod->SetPosition(x, y);
	pod->SetSize(2.0f, 3.0f);
	pod->SetColor(0.3f, 0.3f, 0.7f);
	pod->InitPhysics();
	return pod;
}

PodRacer::PodRacer()
{
	super();
	leftEngine = makeEngine(-2, 5);
	rightEngine = makeEngine(2, 5);
	pod = makePod(0, -2);

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


	b2RopeJointDef podRopeJointDef;
	podRopeJointDef.bodyA = pod->GetBody();
	podRopeJointDef.bodyB = leftEngine->GetBody();
	podRopeJointDef.maxLength = 8.0f;
	podRopeJointDef.collideConnected = true;

	bindPod(podRopeJointDef, -0.75f, 1.5f, 0, -2.0f);
	podRopeJointDef.bodyB = rightEngine->GetBody();
	bindPod(podRopeJointDef, 0.75f, 1.5f, 0, -2.0f);

	// TODO: These should be added when the Pod Racer is added, not when it is instantiated.
	theWorld.Add(leftEngine);
	theWorld.Add(rightEngine);
	theWorld.Add(pod);
}

void PodRacer::Render() {}

void PodRacer::Update(float dt)
{
	if (!theController.IsConnected())
	{
		return;
	}

	float leftTrigger = theController.GetLeftTrigger() / 255.0;
	float rightTrigger = theController.GetRightTrigger() / 255.0;

	Vector2 *zeroVector = new Vector2(0, 0);

	if (leftTrigger > 0.01)
	{
		Vector2 *leftForce = new Vector2(0, leftTrigger);
		leftEngine->ApplyLocalForce(*leftForce, *zeroVector);
		delete leftForce;
	}

	if (rightTrigger > 0.01)
	{
		Vector2 *rightForce = new Vector2(0, rightTrigger);
		rightEngine->ApplyLocalForce(*rightForce, *zeroVector);
		delete rightForce;
	}

}