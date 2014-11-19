#pragma once

#include <stdafx.h>
#include "racer/Racer.h"

/**
 * Controls a pod racer.
 */
class PodController : public Actor
{
public:
	typedef Actor super;
	PodController();
	PodController(Racer *racer);
	void virtual Update(float dt);
	void virtual Render();
	void SetRacer(Racer *racer);
	Racer *GetRacer();
protected:
	Racer *racer;
};