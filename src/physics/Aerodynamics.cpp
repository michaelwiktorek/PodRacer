#include "Aerodynamics.h"
#include <iostream>

#define LIFT 1.0
#define DRAG 1.0

void applyAerodynamics(PhysicsActor *actor, float dragAmount, float liftAmount)
{
	if (liftAmount < 0)
	{
		liftAmount = dragAmount;
	}

	b2Body *body = actor->GetBody();
	b2Vec2 wind = b2Vec2(0, 0);

	for (b2Fixture *fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		b2Shape *shape = fixture->GetShape();

		switch (shape->GetType())
		{
		case b2Shape::e_polygon:
		{
			b2PolygonShape *poly = (b2PolygonShape *) shape;
			int vertexCount = poly->GetVertexCount();
			for (int i = 0; i < vertexCount; i++)
			{
				b2Vec2 v1 = poly->GetVertex(i);
				b2Vec2 v2 = poly->GetVertex((i + 1) % vertexCount);
				applyAerodynamicsToEdge(actor, v1, v2, dragAmount, liftAmount);
			}
			break;
		}
		case b2Shape::e_circle:
		{
			b2CircleShape *circle = (b2CircleShape *) shape;
			b2Vec2 center = body->GetWorldPoint(circle->m_p);
			b2Vec2 airVelocity = body->GetLinearVelocityFromWorldPoint(center) + wind;
			float airSpeed = airVelocity.Normalize();
			float dragMagnitude = circle->m_radius * 2 * airSpeed * dragAmount * theTuning.GetFloat("Drag");
			b2Vec2 drag = dragMagnitude * -airVelocity;
			body->ApplyForce(drag, center);
			break;
		}
		case b2Shape::e_edge:
		{
			b2EdgeShape *edge = (b2EdgeShape *) shape;
			// TODO: Edge shape aerodynamics
			break;
		}
		}
	}
}

void applyAerodynamicsToEdge(PhysicsActor *actor, b2Vec2 &v1, b2Vec2 &v2, float dragAmount, float liftAmount)
{
	if (liftAmount < 0)
	{
		liftAmount = dragAmount;
	}
	b2Body *body = actor->GetBody();

	b2Vec2 w1 = body->GetWorldPoint(v1);
	b2Vec2 w2 = body->GetWorldPoint(v2);

	b2Vec2 midpoint = 0.5 * (w1 + w2);
	b2Vec2 edge = w2 - w1;
	float edgeLength = edge.Normalize();
	b2Vec2 edgeNormal = b2Cross(-1, edge);
	b2Vec2 airVelocity = body->GetLinearVelocityFromWorldPoint(midpoint);
	float airSpeed = airVelocity.Normalize();

	float airDotEdgeNormal = b2Dot(airVelocity, edgeNormal);
	float airDotEdge = b2Dot(airVelocity, edge);
	if (airDotEdgeNormal < 0)
		return;

	// drag
	float dragMagnitude = airDotEdgeNormal * edgeLength * airSpeed * dragAmount * theTuning.GetFloat("Drag");
	b2Vec2 drag = dragMagnitude * -airVelocity;
	body->ApplyForce(drag, midpoint);

	// lift
	float liftMagnitude = airDotEdge * airDotEdgeNormal * edgeLength * airSpeed * liftAmount * theTuning.GetFloat("Lift");
	b2Vec2 lift = liftMagnitude * b2Cross(1, airVelocity);
	body->ApplyForce(lift, midpoint);;
}