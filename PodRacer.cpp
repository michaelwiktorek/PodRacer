#include "PodRacer.h"

/**
 * Draw a line with openGL
 * @param ax [description]
 * @param ay [description]
 * @param bx [description]
 * @param by [description]
 */
void drawLine(float ax, float ay, float bx, float by, Color color, float width)
{
	glLineWidth(width);
	glColor3f(color.R, color.G, color.B);
	glBegin(GL_LINES);
	glVertex3f(ax, ay, 0.0);
	glVertex3f(bx, by, 0);
	glEnd();
}

/**
 * Helper function to create a distance joint between engines.
 */
void bindEngines(b2DistanceJointDef &jointDef, float ay, float by, float length)
{
	jointDef.length = length;
	jointDef.localAnchorA.Set(0.5f, ay); // TODO: Do I have to make a b2Vec2 first?
	jointDef.localAnchorB.Set(-0.5f, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

/**
 * Helper function to create a rope joint between pod and engine.
 */
void bindPod(b2RopeJointDef &jointDef, float ax, float ay, float bx, float by)
{
	jointDef.localAnchorA.Set(ax, ay);
	jointDef.localAnchorB.Set(bx, by);
	theWorld.GetPhysicsWorld().CreateJoint(&jointDef);
}

/**
 * Apply air friction to a physics actor.
 * @param a      the actor
 * @param amount the amount of friction to apply. 1.0 is normal.
 */
void applyAirFriction(PhysicsActor *a, float amount)
{
	b2Vec2 force = a->GetBody()->GetLinearVelocity();
	force *= -amount;
	a->GetBody()->ApplyForceToCenter(force);
}

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
}

/**
 * Create a new engine at (x, y).
 */
PodEngine::PodEngine(float x, float y)
{
	super();
	SetSize(1.0f, 5.0f);
	SetColor(0.3f, 0.3f, 0.3f);
	SetPosition(x, y);
	SetRestitution(0.1f);
	SetFriction(0.2f);
	InitPhysics();

	// TODO: create particle effect.
}

/**
 * Updates the engine.
 */
void PodEngine::Update(float dt)
{
	applyAirFriction(this, theTuning.GetFloat("EngineAirFriction"));
}

/**
 * [PodEngine::Thrust description]
 * @param amount [description]
 */
void PodEngine::Thrust(float amount)
{
	Vector2 thrust = Vector2(0, amount * GetMaxThrust());
	Vector2 point = Vector2(0, 0);
	ApplyLocalForce(thrust, point);
}

/**
 * @return The maximum amount of thrust this engine can produce in its current state.
 */
float PodEngine::GetMaxThrust()
{
	float result = theTuning.GetFloat("EnginePower");
	result += GetBody()->GetLinearVelocity().Length() * 0.01 * result;
	return result;
}

/**
 * Update the pod.
 */
void Pod::Update(float dt)
{
	applyAirFriction(this, theTuning.GetFloat("PodAirFriction"));
}

/**
 * Create a new pod racer.
 */
PodRacer::PodRacer()
{
	super();

	leftEngine = new PodEngine(-2, 5);
	rightEngine = new PodEngine(2, 5);
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
	podRopeJointDef.maxLength = 8.0f;
	podRopeJointDef.collideConnected = true;

	bindPod(podRopeJointDef, -0.75f, 1.5f, 0, -2.0f);
	podRopeJointDef.bodyB = rightEngine->GetBody();
	bindPod(podRopeJointDef, 0.75f, 1.5f, 0, -2.0f);

	// TODO: These should be added when the Pod Racer is added to the world, not when it is instantiated.
	theWorld.Add(leftEngine);
	theWorld.Add(rightEngine);
	theWorld.Add(pod);
}

void PodRacer::Render()
{
	Vector2 leftPos = leftEngine->GetPosition();
	Vector2 rightPos = rightEngine->GetPosition();
	Vector2 podPos = pod->GetPosition();

	drawLine(leftPos.X, leftPos.Y, rightPos.X, rightPos.Y, Color(1, 0, 1), 2.2);
}

void PodRacer::Update(float dt)
{
	if (!theController.IsConnected())
	{
		return;
	}

	// float leftTrigger = theController.GetLeftTrigger() / 255.0;
	// float rightTrigger = theController.GetRightTrigger() / 255.0;
	float leftTrigger = theController.GetLeftThumbstick().Y / 255.0;
	float rightTrigger = theController.GetRightThumbstick().Y / 255.0;

	if (leftTrigger > 0.01)
	{
		leftEngine->Thrust(leftTrigger);
	}

	if (rightTrigger > 0.01)
	{
		rightEngine->Thrust(rightTrigger);
	}

}
