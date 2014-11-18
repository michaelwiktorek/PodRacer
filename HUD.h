#pragma once

#include "stdafx.h"
#include "PodRacer.h"

#define SCALE_FACTOR 400
#define Y_DIST theCamera.GetWindowHeight() + 50

class HUD : public HUDActor 
{
public:
	typedef HUDActor super;
	HUD(PodRacer *);
	virtual void Update(float dt);
	virtual void Render();

	Actor *leftEngineBar;
	Actor *rightEngineBar;
	PodRacer *podRacer;
};