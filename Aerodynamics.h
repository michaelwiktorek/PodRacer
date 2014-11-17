#pragma once

#include "stdafx.h"

void applyAerodynamics(PhysicsActor *actor, float dragAmount = 1.0, float liftAmount = -1.0);
void applyAerodynamicsToEdge(PhysicsActor *actor, b2Vec2 &v1, b2Vec2 &v2, float dragAmount = 1.0, float liftAmount = -1.0);