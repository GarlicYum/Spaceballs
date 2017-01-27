#include "Bullet.h"

void Bullet::Draw(int in_x, int y, Graphics & gfx)
{
	int height = y - bulletSize -vy;
	x = in_x;

	if (height - bulletSize >= 0)
	{
		gfx.DrawCircle(x, height, bulletSize, Colors::Magenta);
	}
	else
	{
		vy = 0;
	}
	vy += 15;	
}
