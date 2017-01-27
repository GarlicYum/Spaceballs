#pragma once
#include "Graphics.h"
#include "Bullet.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void ClampScreen(Graphics& gfx);
	void Shoot(Graphics& gfx);
	int x = 300;
	int y = 300;
private:
	int width = 100;
	int height = 100;
	int canonPos = 50;
	Bullet bullet;
};