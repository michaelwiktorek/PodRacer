#pragma once

#include <stdafx.h>
#include "PodController.h"
#include "race/Race.h"

/**
 * Controls a pod racer with AI.
 */
class AIPodController : public PodController
{
public:
	typedef PodController super;
	AIPodController();
	AIPodController(Racer *racer);
	AIPodController(Racer *racer, Race *race);
	void virtual Update(float dt);
	virtual void SetRace(Race *race);
protected:
	Race *race;
};