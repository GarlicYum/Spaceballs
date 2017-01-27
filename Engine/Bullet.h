#pragma once
#include "Graphics.h"

class Bullet
{
public:
	void Draw(int in_x, int y, Graphics& gfx);
	int vy = 0;
private:
	int bulletSize = 10;
	int x;
};