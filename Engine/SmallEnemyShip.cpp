#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, const Surface & enemySurface)
	:
	pos(x, 200.0f),
	surface(enemySurface)
{}

void SmallEnemyShip::Draw(Graphics & gfx)
{
	gfx.DrawSpriteKey(int(pos.x), int(pos.y), surface, surface.GetPixel(0, 0));
}
