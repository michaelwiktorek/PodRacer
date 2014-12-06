#pragma once

#include "stdafx.h"

class Checkpoint : public Actor
{
public:
	Checkpoint(float x, float y, float z);
	float width;
};