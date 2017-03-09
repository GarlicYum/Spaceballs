#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"
#include "Shield.h"

class SmallShield
{
public:
	SmallShield(float X, float Y);
	void Draw(Graphics& gfx);
	void Update(Ship& ship, float dt, Shield& shield);
	RectF GetCollisionRect() const;
	void HandleCollision(Shield& shield);
	void Reset();

private:
	Vec2 pos;
	float vy = 200.0f;
	static constexpr int radius = 20;
	static constexpr int hole = 18;
	Color c = Colors::Blue;
	bool isObtained = false;
};

