#pragma once

#include <stdafx.h>
#include "PodRacer.h"

/**
 * Controls a pod racer with input from the controller.
 */
class HumanPodController : public Actor
{
public:
	typedef Actor super;
	HumanPodController();
	HumanPodController(PodRacer *podRacer);
	void virtual Update(float dt);
	void virtual Render();
	void SetPodRacer(PodRacer *podRacer);
	PodRacer *GetPodRacer();
private:
	PodRacer *podRacer;
};