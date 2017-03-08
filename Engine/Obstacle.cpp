#include "Obstacle.h"

Obstacle::Obstacle(float X, const Surface & obstacleSurface)
	:
	pos(X, resetY),
	surface(obstacleSurface)
{}

void Obstacle::Draw(Graphics & gfx)
{
	if (pos.y < gfx.ScreenHeight)
	{
		gfx.DrawSpriteAlpha(int(pos.x), int(pos.y), surface);
	}
}

void Obstacle::Update(float dt)
{
	pos.y += vy * dt;
}

void Obstacle::HandleBottomCollision(Ship& ship)
{
	ship.SetY(pos.y + height);
}

void Obstacle::HandleTopCollision(Ship & ship)
{
	ship.SetY(pos.y - ship.GetHeight());
}

void Obstacle::HandleLeftCollision(Ship & ship)
{
	ship.SetX(pos.x - ship.GetWidth());
}

void Obstacle::HandleRightCollision(Ship & ship)
{
	ship.SetX(pos.x + width);
}

RectF Obstacle::GetBottomCollisionRect() const
{
	return RectF(Vec2(pos.x + 10, pos.y + height -1), width - 20, 1);
}

RectF Obstacle::GetLeftCollisionRect() const
{
	return RectF(pos, 1 ,height);
}

RectF Obstacle::GetRightCollisionRect() const
{
	return RectF(Vec2(pos.x + width -1, pos.y), 1, height);
}

RectF Obstacle::GetTopCollisionRect() const
{
	return RectF(Vec2(pos.x + 10, pos.y), width - 20, 1);
}

void Obstacle::Reset()
{
	pos.y = resetY;
}
