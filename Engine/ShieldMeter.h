#pragma once
#include "Graphics.h"

class ShieldMeter
{
public:
	void Draw(Graphics& gfx, int width);
	int GetShieldLevel();
private:
	static constexpr int height = 10;
	static constexpr int x = 400;
	static constexpr int y = 570;
	int shieldLevel = 300;
	static constexpr int maxHealth = 300;
	Color c = Colors::Blue;
};