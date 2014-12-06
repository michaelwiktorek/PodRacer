#include "stdafx.h"
#include "PodGameManager.h"
#include "racer/Racer.h"
#include "racer/racers.h"
#include "HumanPodController.h"
#include "AIPodController.h"
//#include "HUD.h"

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

	Racer *playerRacer = makeAnakinRacer(0, 0);
	theWorld.Add(playerRacer);
	//HUD *hud = new HUD(playerRacer);
	//theWorld.Add(hud);
	theWorld.Add(new HumanPodController(playerRacer));

	Racer *aiRacer = makeSebulbaRacer(10, 0);
	theWorld.Add(aiRacer);
	theWorld.Add(new AIPodController(aiRacer));

	theCamera.SetPosition(0, 0,  25);
	theCamera.LockTo(playerRacer->pod);
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
