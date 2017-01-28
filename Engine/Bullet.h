#pragma once
#include "Graphics.h"

class Bullet
{
public:
	void Spawn(int X, int Y);
	void Update();
	bool HasSpawned() const;
	void Draw(Graphics & gfx);
private:
	int bulletSize = 10;
	int x;
	int y;
	int vy;
	bool hasSpawned = false;
};