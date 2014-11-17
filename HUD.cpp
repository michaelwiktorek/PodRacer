#include "HUD.h"
#include <iostream>

HUD::HUD()
{
	//super();
	// hardcode position of engine bars for now
	leftEngineBar = new HUDActor();
	rightEngineBar = new HUDActor();
	leftPower = 0;
	rightPower = 0;

	leftEngineBar->SetColor(Color(0.5f, 0.3f, 0.3f, 0.6f));
	leftEngineBar->SetSize(50.0f, leftPower*SCALE_FACTOR);
	leftEngineBar->SetPosition(100, Y_DIST);

	rightEngineBar->SetColor(Color(0.5f, 0.3f, 0.3f, 0.6f));
	rightEngineBar->SetSize(50.0f, rightPower*SCALE_FACTOR);
	rightEngineBar->SetPosition(250, Y_DIST);

	// leftText = new TextActor();
	// rightText = new TextActor();

	// leftText->SetPosition(100, Y_DIST+SCALE_FACTOR);
	// rightText->SetPosition(250, Y_DIST+SCALE_FACTOR);

	// leftText->SetDisplayString("hello");
	// rightText->SetDisplayString("hello2");

	theWorld.Add(leftEngineBar);
	theWorld.Add(rightEngineBar);
	// theWorld.Add(leftText);
	// theWorld.Add(rightText);
}

void HUD::Update(float dt)
{
	leftEngineBar->SetSize(100.0f, leftPower*SCALE_FACTOR);
	leftEngineBar->SetPosition(100, Y_DIST-leftPower*SCALE_FACTOR/2);

	rightEngineBar->SetSize(100.0f, rightPower*SCALE_FACTOR);
	rightEngineBar->SetPosition(250, Y_DIST-rightPower*SCALE_FACTOR/2);
}

void HUD::Render()
{
	// call render on both engine bars?
	// and later, other stuff
}

void HUD::SetEngines(float left, float right)
{
	leftPower = left;
	rightPower = right;
}