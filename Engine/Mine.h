#pragma once
#include "Graphics.h"

class Mine
{
public:
	void DetectCollision();
	void Detonate();
	void Update();
	void Draw(Graphics& gfx);
	void SetPos(int X);
private:
	int x = 0;
	int y = 0;
	int vy = 2;
	int explosionCounter = 0;
	static constexpr int explosionEnd = 30;
	bool isDetonated = false;
	bool gotPosition = false;
	static constexpr int damage = 40;
	static constexpr int width = 50;
	static constexpr int height = 50;
};