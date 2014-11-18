#include "stdafx.h"
#include "PodGameManager.h"

int main(int argc, char *argv[])
{

	theWorld.Initialize(1440, 900, "Test Game, Please Ignore", false, true, false); // NOTE: These values are overridden with values from preferences
	theWorld.SetGameManager(&PodGameManager::GetInstance());

	theWorld.StartGame();
	theWorld.Destroy();

	return 0;
}