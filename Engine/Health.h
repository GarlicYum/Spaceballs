#pragma once
#include "Graphics.h"

class Health
{
public:
	Health() = default;
	Health(int X, int Y, int hp);
	void Damage(int dmg);
	void Restore(int restore);
	void Draw(Graphics& gfx);
	bool HasHealth() const; 
	int GetHealthAmount() const;
	void Reset();
	bool FillUp(int amount, int increment, float dt);
	
private:
	void ColorMeter();
	static constexpr int height = 10;
	int x = 25;
	int y = 570;
	int healthAmount = 300;
	static constexpr int maxHealth = 300;
	float timer = 0.0f;
	static constexpr float newincrement = 1.0f / 60.0f;
	Color c = Colors::Green;
};