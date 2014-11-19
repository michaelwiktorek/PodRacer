#pragma once

#include <stdafx.h>
#include "PodRacer.h"

/**
 * Controls a pod racer.
 */
class PodController : public Actor
{
public:
	typedef Actor super;
	PodController();
	PodController(PodRacer *podRacer);
	void virtual Update(float dt);
	void virtual Render();
	void SetPodRacer(PodRacer *podRacer);
	PodRacer *GetPodRacer();
protected:
	PodRacer *podRacer;
};