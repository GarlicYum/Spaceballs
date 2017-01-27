#pragma once
#include "Graphics.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void ClampScreen(Graphics& gfx);
	void Shoot(Graphics& gfx);
	int x = 300;
	int y = 300;
	int vy = 0;
private:
	int width = 100;
	int height = 100;
	int bulletSize = 7;
};