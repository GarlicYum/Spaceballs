#include "Bullet.h"

//Anything I want to draw on screen should have an update function and a draw function

//Spawn gets x and y positions which are the position of the canon
//it gets called from ships firebullet function
void Bullet::Spawn(int X, int Y) 
{
	if (!hasSpawned) //if a bullet has NOT been spawned it sets the bullets pos to the canon pos
	{
		x = X;
		y = Y - bulletSize;
		vy = 15;
		hasSpawned = true; //change has spawn to true, this way fired bullet wont follow the ships x pos
	}
}

void Bullet::Update()
{
	y -= vy;

	if (y - bulletSize < 0) //if bullet reaches end of screen, hasspawned becomes false and bullet will no longer be drawn
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