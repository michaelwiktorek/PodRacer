#include "stdafx.h"
#include "PodGameManager.h"


void init_game()
{
	theWorld.SetSideBlockers(true, 0.7f);
	theWorld.Add(new GridActor(), -1);
}

int main(int argc, char *argv[])
{
    theWorld.Initialize(800, 600, "Test Game, Please Ignore", true, false, true);
    theWorld.SetupPhysics(*(new Vector2(0, 0))); // TODO: Don't leak memory

    init_game();

    theWorld.SetGameManager(&PodGameManager::GetInstance());
    theWorld.StartGame();
    theWorld.Destroy();

    return 0;
}