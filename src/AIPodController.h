#pragma once

#include <stdafx.h>
#include "PodController.h"

/**
 * Controls a pod racer with input from the controller.
 */
class AIPodController : public PodController
{
public:
	using PodController::PodController;
	typedef PodController super;
	void virtual Update(float dt);
};