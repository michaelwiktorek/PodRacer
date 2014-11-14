#include "stdafx.h"
#include "PodGameManager.h"

int main(int argc, char *argv[])
{

	theWorld.Initialize(800, 600, "Test Game, Please Ignore", false, false, false); // NOTE: These values are overridden with values from preferences
	theWorld.SetupPhysics(*(new Vector2(0, 0))); // TODO: Don't leak memory
	theWorld.SetGameManager(&PodGameManager::GetInstance());

	theWorld.StartGame();
	theWorld.Destroy();

	return 0;
}