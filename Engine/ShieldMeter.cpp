#include "ShieldMeter.h"

void ShieldMeter::Draw(Graphics& gfx, int width)
{
	gfx.DrawSquare(x, y, width, height, c);
}
