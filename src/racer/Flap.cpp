#include "Racer.h"
#include <physics/Aerodynamics.h>
#include <math.h>

Flap::Flap(float l, Vector2 pos, Color c, Side s, float d, float max)
{
	length = l;
	position = pos;
	color = c;
	side = s;
	drag = d;
	maximumAngle = max;
	activation = 0.0;
}

void Flap::Render(PhysicsActor *actor)
{
	float sign = (side == Flap::LEFT) ? 1 : -1;
	Vector2 end = position + MathUtil::VectorFromAngle(sign *  activation * maximumAngle + 90) * length;
	drawLine(localToWorld(actor, position), localToWorld(actor, end), color, 1);
}

void Flap::Update(PhysicsActor *actor)
{
	// TODO: Apply lift? Apply aerodynamics based on angle?
	b2Vec2 start = b2Vec2(position.X, position.Y);
	float dx = (side == Flap::RIGHT) ? length : -length;
	float dy = 0.0;
	b2Vec2 end = start + b2Vec2(dx, dy);
	float d = drag * sin(MathUtil::ToRadians(activation * maximumAngle)) ;
	if (side == Flap::LEFT)
	{
		applyAerodynamicsToEdge(actor, start, end, d, 0.0);
	}
	else
	{
		applyAerodynamicsToEdge(actor, end, start, d, 0.0);
	}
}