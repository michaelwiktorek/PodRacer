#include "Checkpoint.h"

Checkpoint::Checkpoint(float x, float y, float w)
{
	SetPosition(x, y);
	width = w;

	SetSize(Vector2(w, w));
	SetColor(Color(0, 0, 1, 0.1));
	SetDrawShape(ADS_Circle);
}
