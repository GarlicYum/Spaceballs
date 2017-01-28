#include "Bullet.h"

void Bullet::Spawn(int X, int Y)
{
	if (!hasSpawned)
	{
		x = X;
		y = Y - bulletSize;
		vy = 15;
		hasSpawned = true;
	}
}

void Bullet::Update()
{
	y -= vy;

	if (y - bulletSize < 0)
	{
		y = 0;
		hasSpawned = false;
	}
}

bool Bullet::HasSpawned() const
{
	return hasSpawned;
}

void Bullet::Draw(Graphics& gfx)
{
	gfx.DrawCircle(x, y, bulletSize, Colors::Magenta);
}