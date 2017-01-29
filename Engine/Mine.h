#pragma once
#include "Graphics.h"

class Mine
{
public:
	int Detonate();
	void Update(int X, int Y);
	void Draw(Graphics& gfx);
private:
	int x;
	int y;
	int vy = 2;
	bool isDetonated = false;
	bool gotPosition = false;
	static constexpr int damage = 40;
	static constexpr int width = 50;
	static constexpr int height = 50;
};