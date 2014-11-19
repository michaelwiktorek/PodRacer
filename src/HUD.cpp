#include "HUD.h"
#include <iostream>

HUD::HUD(Racer *racer)
{
	//super();
	this->racer = racer;

	// hardcode position of engine bars for now
	leftEngineBar = new HUDActor();
	rightEngineBar = new HUDActor();

	leftEngineBar->SetColor(Color(0.5f, 0.3f, 0.3f, 0.6f));
	leftEngineBar->SetSize(50.0f, racer->leftEngine->throttle * SCALE_FACTOR);
	leftEngineBar->SetPosition(100, Y_DIST);

	rightEngineBar->SetColor(Color(0.5f, 0.3f, 0.3f, 0.6f));
	rightEngineBar->SetSize(50.0f, racer->rightEngine->throttle * SCALE_FACTOR);
	rightEngineBar->SetPosition(250, Y_DIST);

	// theWorld.Add(leftEngineBar);
	// theWorld.Add(rightEngineBar);
}

void HUD::Update(float dt)
{
	leftEngineBar->SetSize(100.0f, racer->leftEngine->throttle * SCALE_FACTOR);
	leftEngineBar->SetPosition(100, Y_DIST - racer->leftEngine->throttle * SCALE_FACTOR / 2);

	rightEngineBar->SetSize(100.0f, racer->rightEngine->throttle * SCALE_FACTOR);
	rightEngineBar->SetPosition(250, Y_DIST - racer->rightEngine->throttle * SCALE_FACTOR / 2);
}

void HUD::Render()
{
	//super::Render();
	// rightEngineBar->Render();
	// leftEngineBar->Render();
	// DrawGameText("Left Engine", "Console", 50, Y_DIST-SCALE_FACTOR, 0);
	// DrawGameText("Right Engine", "Console", 200, Y_DIST-SCALE_FACTOR, 0);
}