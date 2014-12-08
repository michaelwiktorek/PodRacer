#include "stdafx.h"
#include "PodGameManager.h"
#include "race/Race.h"
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

	theWorld.NameLayer("Ground", 20);
	theWorld.NameLayer("Main", 10);
	theWorld.NameLayer("Racers", 0);
	theWorld.NameLayer("HUD", -10);
	theWorld.Add(new GridActor(
	                 Color(0.8, 0.8, 1.0),
	                 Color(1.0, 0, 0),
	                 5.0,
	                 Vector2(-5000, -5000),
	                 Vector2(5000, 5000)
	             ), -1);

	Race *race = new Race();
	theWorld.Add(race, "Main");
	Racer *playerRacer = makeSebulbaRacer(0, 0);
	playerRacer->pod->SetColor(Color(0, 0, 0));
	playerRacer->leftEngine->SetColor(Color(0, 0, 0));
	playerRacer->rightEngine->SetColor(Color(0, 0, 0));
	race->AddRacer(playerRacer);
	theWorld.Add(new HumanPodController(playerRacer));

	//HUD *hud = new HUD(playerRacer);
	//theWorld.Add(hud);

	// Racer *aiRacer = makeSebulbaRacer(10, 0);
	Racer *aiRacer;
	int numRacers = 5;
	for (int i = 0; i < numRacers; i++)
	{
		if (i % 2 == 0)
		{
			aiRacer = makeAnakinRacer(i * 4 - 5, -5);
		}
		else
		{
			aiRacer = makeSebulbaRacer(i * 4 - 5, -5);
		}
		race->AddRacer(aiRacer);
		AIPodController *controller = new AIPodController(aiRacer, race);
		controller->SetDifficulty(0.0 * (float)i / numRacers + 0.95);
		theWorld.Add(controller);
	}

	theCamera.SetPosition(0, 0,  28);
	theCamera.LockTo(aiRacer);
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

/**
 * Receive messages that have been registered.
 * @param message [description]
 */
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
