#pragma once
#include "Graphics.h"

class Health
{
public:
	void Damage(int dmg);
	void Restore(int restore);
	void Draw(Graphics& gfx);
	bool HasHealth() const; 
	
private:
	void ColorMeter();
	static constexpr int height = 10;
	static constexpr int x = 50;
	static constexpr int y = 570;
	int healthAmount = 300;
	static constexpr int maxHealth = 300;
	Color c = Colors::Green;
};