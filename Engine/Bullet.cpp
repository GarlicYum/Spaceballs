#include "Bullet.h"

Bullet::Bullet(float X, float Y)
	:
	x(X),
	y(Y),
	bState(AliveState)
{}

void Bullet::Update(float dt)
{
	y -= vy * dt;

	if (y - bulletSize < 0)
	{
		bState = DeadState;
	}
}

bool Bullet::HasSpawned() const
{
	return bState == AliveState;
}

void Bullet::Draw(Graphics& gfx)
{
	gfx.DrawCircle(int(x), int(y), bulletSize, Colors::Magenta);
}

bool Bullet::IsActive() const
{
	return bState == AliveState;
}

RectF Bullet::GetCollisionRect() const
{
	const float bSize = float(bulletSize);
	return RectF(
		x - bSize,
		y - bSize,
		(bSize * 2.0f),
		(bSize * 2.0f));
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}