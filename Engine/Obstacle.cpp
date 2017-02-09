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

void Obstacle::HandleBottomCollision(Ship& ship)
{
	ship.SetY(y + height);
}

void Obstacle::HandleTopCollision(Ship & ship)
{
	ship.SetY(y - ship.GetHeight());
}

void Obstacle::HandleLeftCollision(Ship & ship)
{
	ship.SetX(x - ship.GetWidth());
}

void Obstacle::HandleRightCollision(Ship & ship)
{
	ship.SetX(x + width);
}

RectF Obstacle::GetBottomCollisionRect() const
{
	return RectF(x + 10, y + height -1, width - 20, 1);
}

RectF Obstacle::GetLeftCollisionRect() const
{
	return RectF(x, y, 1 ,height);
}

RectF Obstacle::GetRightCollisionRect() const
{
	return RectF(x + width -1, y, 1, height);
}

RectF Obstacle::GetTopCollisionRect() const
{
	return RectF(x + 10, y, width - 20, 1);
}
