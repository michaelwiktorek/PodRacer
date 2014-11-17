#include "stdafx.h"
#include "PodGameManager.h"
#include "PodRacer.h"

/**
 * Create a new game manager. This is the top level of control for the game.
 */
PodGameManager::PodGameManager()
{
	theSwitchboard.SubscribeTo(this, "MoveForwards");
	theSwitchboard.SubscribeTo(this, "MoveBackwards");

	theWorld.SetupPhysics(Vector2(0, 0),
	                      Vector2(5000, 5000),
	                      Vector2(-5000, -5000));

	// theWorld.SetSideBlockers(true, 0.7f);
	theWorld.Add(new GridActor(
	                 Color(0.8, 0.8, 1.0),
	                 Color(1.0, 0, 0),
	                 5.0,
	                 Vector2(-5000, -5000),
	                 Vector2(5000, 5000)
	             ), -1);

	PodRacer *podRacer = new PodRacer();
	theWorld.Add(podRacer);

	theCamera.SetPosition(0, 0, 40);
	theCamera.LockTo(podRacer->pod);
}

/** The only instance of this class. */
PodGameManager *PodGameManager::instance = NULL;

/**
 * @return the only instance of this class.
 */
PodGameManager &PodGameManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new PodGameManager();
	}
	return *instance;
}

void PodGameManager::ReceiveMessage(Message *message) {}

/**
 * Called every frame to update game state.
 * @param dt number of seconds since the last frame.
 */
void PodGameManager::Update(float dt) {}


/**
 * Called every frame to draw the world.
 */
void PodGameManager::Render() {}