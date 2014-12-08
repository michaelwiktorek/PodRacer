#pragma once

#include <stdafx.h>
#include <vector>


/**
 * A data class for information about drawing a coupling beam.
 * NOTE: Not used for actual physics calculations.
 */
class CouplingBeam
{
public:
	/**
	 * Create a new coupling beam and set all parameters.
	 */
	CouplingBeam(Vector2 left, Vector2 right, float w, Color c)
	{
		leftPosition = left;
		rightPosition = right;
		width = w;
		color = c;
	};
	/**
	 * Position on the left engine.
	 */
	Vector2 leftPosition;
	/**
	 * Position on the right engine.
	 */
	Vector2 rightPosition;
	/**
	 * Width of the beam in pixels.
	 */
	float width;
	/**
	 * Color of the beam.
	 */
	Color color;
};

/**
 * A flap used for steering and braking.
 */
class Flap
{
public:
	enum Side : bool
	{
		LEFT = true,
		RIGHT = false
	};

	/**
	 * Create a new flap.
	 */
	Flap(float l, Vector2 pos, Color c, Side s, float d, float max);
	/**
	 * Render the flap on the actor.
	 * @param actor
	 */
	virtual void Render(PhysicsActor *actor);
	/**
	 * Apply the physics of the flap to the actor.
	 * @param actor
	 */
	virtual void Update(PhysicsActor *actor);

	/**
	 * Length of the flap
	 */
	float length;
	/**
	 * Local position of the flap.
	 */
	Vector2 position;
	/**
	 * Color of the flap.
	 */
	Color color;
	/**
	 * Left of Right flap.
	 */
	Side side;
	/**
	 * Effectiveness of this flap.
	 */
	float drag;
	/**
	 * The angle in radians when this flap is fully activated.
	 */
	float maximumAngle;
	/**
	 * The percent this flap is currently active. Between 0.0 and 1.0.
	 */
	float activation;
};

/**
 * The engine of a pod racer. Has flaps to steer.
 */
class Engine : public PhysicsActor
{
public:
	typedef PhysicsActor super;

	/**
	 * Create a new Engine at position (x, y).
	 */
	Engine(float x, float y);
	virtual void Update(float dt);
	virtual void Render();
	/**
	 * Finalizes engine and pod sizes. Creates joints.
	 */
	virtual void Init();
	/**
	 * Set the activation amount of the left flap.
	 * @param x between 0.0 and 1.0
	 */
	virtual void SetLeftFlap(float x);
	/**
	 * Set the activation amount of the left flap.
	 * @param x between 0.0 and 1.0
	 */
	virtual void SetRightFlap(float x);
	/**
	 * The maximum amount of thrust this engine can currently output.
	 */
	virtual float GetMaxThrust();
	/**
	 * Set the throttle amount
	 * @param throttle between 0.0 and 1.0.
	 */
	virtual void SetThrottle(float throttle);
	/**
	 * Add a flap to this engine.
	 * @param flap
	 */
	virtual void AddFlap(Flap flap);

	/**
	 * The particle effect for the exhaust.
	 */
	ParticleActor *exhaust;
	/**
	 * An amount to scale this engine's thrust output by.
	 */
	float baseThrust;
	/**
	 * Color of the meter bar.
	 */
	Color meterColor;
	/**
	 * Color of the back of the meter bar.
	 */
	Color meterBackColor;
	/**
	 * Width in pixels of the meter bar.
	 */
	float meterWidth;
protected:
	/**
	 * All the flaps on this engine.
	 */
	std::vector<Flap> flaps;
	/**
	 * The actual amount the throttle is at.
	 */
	float throttle;

};

/**
 * The pod where the pilot sits.
 */
class Pod : public PhysicsActor
{
public:
	typedef PhysicsActor super;
	Pod(float x, float y);
	virtual void Update(float dt);
	virtual void Render();
	/**
	 * Finalizes engine and pod sizes. Creates joints.
	 */
	virtual void Init();
	/**
	 * Set the activation amount of the left flap.
	 * @param x between 0.0 and 1.0
	 */
	virtual void SetLeftFlap(float x);
	/**
	 * Set the activation amount of the left flap.
	 * @param x between 0.0 and 1.0
	 */
	virtual void SetRightFlap(float x);
	/**
	 * Add a flap to this pod.
	 * @param flap
	 */
	virtual void AddFlap(Flap flap);
protected:
	/**
	 * All the flaps on this pod.
	 */
	std::vector<Flap> flaps;
};

/**
 * The owner of the two engines and a pod.
 */
class Racer : public Actor
{
public:
	typedef Actor super;
	Racer(float x, float y);
	virtual void Render();
	virtual void Update(float dt);
	/**
	 * Finalizes engine and pod sizes. Creates joints.
	 */
	virtual void Init();
	/**
	 * Set the left flaps on the pod and engines.
	 * @param x
	 */
	virtual void SetLeftFlaps(float x);
	/**
	 * Set the right flaps on the pod and engines.
	 * @param x
	 */
	virtual void SetRightFlaps(float x);
	/**
	 * Set the base distance between the engines.
	 * @param d
	 */
	virtual void SetEngineDistance(float d);
	/**
	 * Set the base length of the ropes from the pod to the engines.
	 * @param d
	 */
	virtual void SetRopeLength(float d);
	/**
	 * Set the base power of the engines.
	 * @param p 1.0 is standard
	 */
	virtual void SetBaseThrust(float p);
	/**
	 * Set the size of each of the engines.
	 * @param width
	 * @param height
	 */
	virtual void SetEngineSize(float width, float height);
	/**
	 * Set the color of the engine meter.
	 * @param front color of the bar
	 * @param back  color of the bar background
	 */
	virtual void SetEngineMeterColor(Color front, Color back);
	/**
	 * Set the strength of the engine couplings
	 * @param f
	 */
	virtual void SetCouplingStrength(float f);
	/**
	 * The amount the engines oscillate, relative to their base distance.
	 * @param f
	 */
	virtual void SetCouplingOscillationAmount(float f);
	/**
	 * The frequency the engines oscillate at.
	 * @param f
	 */
	virtual void SetCouplingOscillationRate(float f);
	/**
	 * @return World coordinates.
	 */
	virtual Vector2 GetPosition();
	/**
	 * Get the velocity vector of the pod or something.
	 * @return velocity vector
	 */
	virtual Vector2 GetVelocity();
	/**
	 * Get the velocity vector of the pod or something.
	 * @return velocity vector
	 */
	virtual float GetDirection();

	/**
	 * The left engine of this racer
	 */
	Engine *leftEngine;
	/**
	 * The right engine of this racer
	 */
	Engine *rightEngine;
	/**
	 * The pod engine of this racer
	 */
	Pod *pod;
	/**
	 * The joints holding the engines together.
	 */
	b2DistanceJoint *engineCouplings[4];
	/**
	 * The joint attaching the left engine to the pod.
	 */
	b2RopeJoint *leftRope;
	/**
	 * The joint attaching the right engine to the pod.
	 */
	b2RopeJoint *rightRope;
	/**
	 * List of coupling beams that store information about each beam.
	 */
	std::vector<CouplingBeam> couplingBeams;
protected:
	/**
	 * Amount of time that has passed. Used for oscillating stuff.
	 */
	float t;
	/**
	 * Amount of oscillation in the engines.
	 */
	float couplingOscillationAmount;
	/**
	 * Frequency of oscillation in the engines.
	 */
	float couplingOscillationRate;
	/**
	 * The rigidity of the engine couplings.
	 */
	float couplingStrength;
	/**
	 * The base lengths of the engineCouplings.
	 */
	float couplingLengths[4];
	/**
	 * The base length of the ropes.
	 */
	float ropeLength;
};