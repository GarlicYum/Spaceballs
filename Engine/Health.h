#pragma once
#include "Graphics.h"

class Health
{
public:
	Health() = default;
	Health(int X, int Y, Color C);
	void Damage(int dmg);
	void Restore(int restore);
	void Draw(Graphics& gfx);
	bool HasHealth() const; 
	int GetHealthAmount() const;
	void Reset();
	
private:
	void ColorMeter();
	static constexpr int height = 10;
	int x = 50;
	int y = 570;
	int healthAmount = 300;
	static constexpr int maxHealth = 300;
	Color c = Colors::Green;
};