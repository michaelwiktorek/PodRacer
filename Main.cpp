#include "stdafx.h"
#include "PodGameManager.h"

int main(int argc, char *argv[])
{

	theWorld.Initialize(800, 600, "Test Game, Please Ignore", false, false, false); // NOTE: These values are overridden with values from preferences
	theWorld.SetGameManager(&PodGameManager::GetInstance());

	theWorld.StartGame();
	theWorld.Destroy();

	return 0;
}