#include "SmallEnemyShip.h"

SmallEnemyShip::SmallEnemyShip(float x, const Surface & enemySurface)
	:
	pos(x, resetY),
	resetX(x),
	surface(enemySurface)
{}

void SmallEnemyShip::Draw(Graphics & gfx)
{
	gfx.DrawSpriteKey(int(pos.x), int(pos.y), surface, surface.GetPixel(0, 0));
}

void SmallEnemyShip::Reset()
{
	pos.y = resetY;
	pos.x = resetX;
}
