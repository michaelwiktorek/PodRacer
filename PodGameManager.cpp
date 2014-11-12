#include "stdafx.h"
#include "PodGameManager.h"
#include "PodRacer.h"


PodGameManager::PodGameManager()
{
	theSwitchboard.SubscribeTo(this, "MoveForwards");
	theSwitchboard.SubscribeTo(this, "MoveBackwards");

	PodRacer *podRacer = new PodRacer();
	theWorld.Add(podRacer);

	theCamera.SetPosition(0, 0, 20);
	theCamera.LockTo(podRacer->pod);
}

PodGameManager *PodGameManager::instance = NULL;

PodGameManager &PodGameManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new PodGameManager();
	}
	return *instance;
}

void PodGameManager::ReceiveMessage(Message *message) {}

void PodGameManager::Update(float dt) {}

void PodGameManager::Render() {}