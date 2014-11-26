#include "stdafx.h"
#include "PodGameManager.h"
#include "racer/Racer.h"
#include "HumanPodController.h"
#include "AIPodController.h"
//#include "HUD.h"

Racer *makeAnakinRacer(float x, float y)
{
	Racer *racer = new Racer(x, y);
	racer->SetName("Anakin");
	racer->pod->SetName("AnakinPod");
	racer->SetEngineSize(0.4, 2.0);
	racer->pod->SetSize(0.8, 1.2);
	racer->couplingBeams[0] = CouplingBeam(
	                              Vector2(0.2, 0.4),
	                              Vector2(-0.2, 0.4),
	                              2.0, Color(0.8, 0, 1));
	racer->SetCouplingStrength(3.5);
	racer->SetCouplingOscillationAmount(0.04);
	racer->SetCouplingOscillationRate(17);
	racer->SetRopeLength(4.0);
	racer->SetEngineDistance(1.4);
	racer->SetBaseThrust(0.8);

	Flap flap = Flap(0.25, Vector2(-0.4, 0), Color(0, 0, 0), Flap::LEFT, 4.5, 80);
	racer->pod->AddFlap(flap);
	flap.side = Flap::RIGHT;
	flap.position.X = 0.4;
	racer->pod->AddFlap(flap);

	flap.drag = 2.0;
	flap.maximumAngle = 20;
	flap.color = Color(0.8, 0.8, 0);
	flap.position = Vector2(0.2, 0.8);
	flap.length = 1.0;
	racer->leftEngine->AddFlap(flap);
	racer->rightEngine->AddFlap(flap);
	flap.position.X = -0.2;
	flap.side = Flap::LEFT;
	racer->leftEngine->AddFlap(flap);
	racer->rightEngine->AddFlap(flap);

	racer->Init();
	return racer;
}

Racer *makeSebulbaRacer(float x, float y)
{
	Racer *racer = new Racer(x, y);
	racer->SetName("Sebulba");
	racer->pod->SetName("SebulbaPod");
	racer->SetEngineSize(2.5, 6);
	racer->pod->SetSize(1.2, 3.5);
	racer->pod->SetColor(Color(1.0, 0.5, 0));
	racer->leftEngine->SetColor(Color(1.0, 0.5, 0));
	racer->rightEngine->SetColor(Color(1.0, 0.5, 0));
	racer->SetEngineMeterColor(Color(1, 1, 1), Color(0, 0, 0));
	racer->SetRopeLength(12);
	racer->couplingBeams.pop_back();
	racer->couplingBeams.push_back(CouplingBeam(
	                                   Vector2(1.2, 0.0),
	                                   Vector2(-1.2, 1.0),
	                                   3.0, Color(0.8, 0, 1)));
	racer->couplingBeams.push_back(CouplingBeam(
	                                   Vector2(1.2, 1.0),
	                                   Vector2(-1.2, 0.0),
	                                   3.0, Color(0.8, 0, 1)));
	racer->SetCouplingStrength(5.5);
	racer->SetCouplingOscillationAmount(0.1);
	racer->SetCouplingOscillationRate(8);
	racer->SetEngineDistance(2.0);
	racer->Init();
	return racer;
}

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
