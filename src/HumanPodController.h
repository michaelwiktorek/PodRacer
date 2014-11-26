#pragma once

#include <stdafx.h>
#include "PodController.h"

/**
 * Controls a pod racer from the controller.
 */
class HumanPodController : public PodController
{
public:
	using PodController::PodController;
	typedef PodController super;
	void virtual Update(float dt);
};