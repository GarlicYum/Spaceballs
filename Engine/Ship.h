#pragma once
#include "Graphics.h"
#include "Bullet.h"

class Ship
{
public:
	void Draw(Graphics& gfx);
	void ClampScreen();
	int GetCannonX() const;
	int GetCannonY() const;
	void SetVelocity(int X, int Y);
	void Update();
	int x = 300;
	int y = 300;
private:
	int width = 100;
	int height = 100;
	int canonPos = 50;
	int vx = 0;
	int vy = 0;
};