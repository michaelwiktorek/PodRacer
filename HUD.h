#pragma once

#include "stdafx.h"

class HUD : public HUDActor 
{
public:
	//typedef HUDActor super;
	HUD();
	virtual void Update(float dt);
	virtual void Render();
	void SetEngines(float left, float right);

	Actor *leftEngineBar;
	Actor *rightEngineBar;
	float leftPower;
	float rightPower;
};