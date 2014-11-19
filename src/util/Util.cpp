#include "Util.h"


Vector2 localToWorld(Actor *a, float x, float y)
{
	float angle = MathUtil::ToRadians(a->GetRotation());
	float c = cos(angle);
	float s = sin(angle);
	return Vector2(c * x - s * y, c * y + s * x) + a->GetPosition();;
}

Vector2 localToWorld(Actor *a, Vector2 &v)
{
	return localToWorld(a, v.X, v.Y);
}

void drawLine(float ax, float ay, float bx, float by, Color color, float width)
{
	glLineWidth(width);
	glColor4f(color.R, color.G, color.B, color.A);
	glBegin(GL_LINES);
	glVertex3f(ax, ay, 0.0);
	glVertex3f(bx, by, 0);
	glEnd();
}

void drawLine(Vector2 a, Vector2 b, Color color, float width)
{
	drawLine(a.X, a.Y, b.X, b.Y, color, width);
}