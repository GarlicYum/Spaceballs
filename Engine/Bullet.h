#pragma once
#include "Graphics.h"

class Bullet
{
public:
	void Draw(int in_x, int y, Graphics& gfx);
private:
	int bulletSize = 10;
	int x;
	int vy = 0;
};