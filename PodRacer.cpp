#include "PodRacer.h"
#include "Aerodynamics.h"
#include <math.h>

/**
 * Convert a local point to a world point for an actor.
 * @param  a The actor
 * @param  x Local X coordinate
 * @param  y Local Y coordinate
 * @return World Coordinate
 */
Vector2 localToWorld(Actor *a, float x, float y)
{
	float angle = MathUtil::ToRadians(a->GetRotation());
	float c = cos(angle);
	float s = sin(angle);
	return Vector2(c * x - s * y, c * y + s * x) + a->GetPosition();;
}

/**
 * Convert a local point to a world point for an actor.
 * @param  a The actor
 * @param  v The local point
 * @return World Coordinate
 */
Vector2 localToWorld(Actor *a, Vector2 &v)
{
	return localToWorld(a, v.X, v.Y);
}

/**
 * Draw a line with openGL.
 * @param ax start x in world coordinates
 * @param ay start y  in world coordinates
 * @param bx end x in world coordinates
 * @param by end y in world coordinates
 * @param color line color
 * @param width line width in pixels
 */
void drawLine(float ax, float ay, float bx, float by, Color color, float width)
{
	glLineWidth(width);
	glColor4f(color.R, color.G, color.B, color.A);
	glBegin(GL_LINES);
	glVertex3f(ax, ay, 0.0);
	glVertex3f(bx, by, 0);
	glEnd();
}

/**
 * @param a     start point in world coordinates
 * @param b     end point in world coordinates
 * @param color line color
 * @param width line width in pixels
 */
void drawLine(Vector2 a, Vector2 b, Color color, float width)
{
	drawLine(a.X, a.Y, b.X, b.Y, color, width);
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
 * Create a new engine at (x, y).
 */
PodEngine::PodEngine(float x, float y)
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

void PodEngine::SetLeftFlap(float x)
{
	leftFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}

void PodEngine::SetRightFlap(float x)
{
	rightFlap = MathUtil::Clamp(x, 0.0f, 1.0f);
}

/**
 * @return The maximum amount of thrust this engine can produce in its current state.
 */
float PodEngine::GetMaxThrust()
{
	float result = theTuning.GetFloat("EnginePower");
	result += GetBody()->GetLinearVelocity().Length() * 0.0005 * result;
	return result;
}

/**
 * Updates the engine.
 */
void PodEngine::Update(float dt)
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

void PodEngine::Render()
{
	super::Render();
	drawLine(localToWorld(this, 0, 1.8), localToWorld(this, 0, -1.8), Color(0, 1, 1), 1);

	Vector2 leftStart = Vector2(-0.5, 1);
	Vector2 leftEnd = leftStart + Vector2(-sin(leftFlap), cos(leftFlap)) * 0.8;
	drawLine(localToWorld(this, leftStart), localToWorld(this, leftEnd), Color(0, 0, 0), 1);
	Vector2 rightStart = Vector2(0.5, 1);
	Vector2 rightEnd = rightStart + Vector2(sin(rightFlap), cos(rightFlap)) * 0.8;
	drawLine(localToWorld(this, rightStart), localToWorld(this, rightEnd), Color(0, 0, 0), 1);
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
 * Update the pod.
 */
void Pod::Update(float dt)
{
	applyAerodynamics(this, theTuning.GetFloat("PodDrag"));
}


/**
 * Create a new pod racer.
 */
PodRacer::PodRacer()
{
	super();
	t = 0;

	leftEngine = new PodEngine(-2, 5);
	rightEngine = new PodEngine(2, 5);
	pod = new Pod(0, -2);
	hud = new HUD();

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
	theWorld.Add(hud);
}

/**
 * Draw the binding between the engines and the ropes from the pod to the engines.
 */
void PodRacer::Render()
{
	Color beamColor = Color(0.8, 0, 1, (sin(t * 40) + 4) / 8);
	drawLine(localToWorld(leftEngine, 0.5, 1), localToWorld(rightEngine, -0.5, 1), beamColor, 2.2);
	Color ropeColor = Color(0.1, 0.1, 0.1);
	drawLine(localToWorld(leftEngine, 0, -2), localToWorld(pod, -0.75, 1.5), ropeColor, 1.0);
	drawLine(localToWorld(rightEngine, 0, -2), localToWorld(pod, 0.75, 1.5), ropeColor, 1.0);
}

/**
 * Apply the player input to the pod.
 */
void PodRacer::Update(float dt)
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

	leftEngine->throttle = leftThrottle;
	rightEngine->throttle = rightThrottle;

	UpdateHUD();
}

void PodRacer::UpdateHUD()
{
	hud->SetEngines(leftEngine->throttle, rightEngine->throttle);
}
