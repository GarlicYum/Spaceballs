#include "Obstacle.h"

Obstacle::Obstacle(float X, const Surface & obstacleSurface)
	:
	x(X),
	surface(obstacleSurface)
{}

void Obstacle::Draw(Graphics & gfx)
{
	if (y < gfx.ScreenHeight)
	{
		gfx.DrawSpriteKey(int(x), int(y), surface, surface.GetPixel(0, 0));
	}
}

void Obstacle::Update(float dt)
{
	y += vy * dt;
}

void Obstacle::HandleCollision(Ship& ship)
{
	ship.SetY(y + height);
}

RectF Obstacle::GetCollisionRect()
{
	return RectF(x, y, width, height);
}
