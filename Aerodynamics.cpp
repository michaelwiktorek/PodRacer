#include "Aerodynamics.h"
#include <iostream>

#define LIFT 1.0
#define DRAG 1.0

void applyAerodynamics(PhysicsActor *actor, float amount)
{
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
				b2Vec2 v1 = body->GetWorldPoint(poly->GetVertex(i));
				b2Vec2 v2 = body->GetWorldPoint(poly->GetVertex((i + 1) % vertexCount));
				b2Vec2 midpoint = 0.5 * (v1 + v2);
				b2Vec2 edge = v2 - v1;
				float edgeLength = edge.Normalize();
				b2Vec2 edgeNormal = b2Cross(-1, edge);
				b2Vec2 airVelocity = body->GetLinearVelocityFromWorldPoint(midpoint) + wind;
				float airSpeed = airVelocity.Normalize();

				float airDotEdgeNormal = b2Dot(airVelocity, edgeNormal);
				float airDotEdge = b2Dot(airVelocity, edge);
				if (airDotEdgeNormal < 0)
					continue;

				// drag
				float dragMagnitude = airDotEdgeNormal * edgeLength * airSpeed * amount * DRAG;
				b2Vec2 drag = dragMagnitude * -airVelocity;
				body->ApplyForce(drag, midpoint);

				// lift
				float liftMagnitude = airDotEdge * airDotEdgeNormal * edgeLength * airSpeed * amount * LIFT;
				b2Vec2 lift = liftMagnitude * b2Cross(1, airVelocity);
				body->ApplyForce(lift, midpoint);;
			}

			break;
		}
		case b2Shape::e_circle:
			// What to do with this?
			break;
		}
	}
}