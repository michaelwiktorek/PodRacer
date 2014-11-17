#pragma once

#include "stdafx.h"
#define SCALE_FACTOR 400
#define Y_DIST theCamera.GetWindowHeight() + 50
class HUD : public HUDActor 
{
public:
	//typedef HUDActor super;
	HUD();
	virtual void Update(float dt);
	virtual void Render();
	void SetEngines(float left, float right);

	// TextActor *leftText;
	// TextActor *rightText;
	HUDActor *leftEngineBar;
	HUDActor *rightEngineBar;
	float leftPower;
	float rightPower;
};