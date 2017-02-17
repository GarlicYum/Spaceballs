#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"
#include "Shield.h"

class SmallShield
{
public:
	void Draw(Graphics& gfx);
	void Update(Ship& ship, float dt, Shield& shield);
	RectF GetCollisionRect() const;
	void HandleCollision(Shield& shield);
	void SetPos(float X);
	void Reset();

private:
	Vec2 pos;
	static constexpr float resetY = -40.0f;
	float vy = 4.0f * 60.0f;
	static constexpr int radius = 20;
	static constexpr int hole = 18;
	Color c = Colors::Blue;
	bool isObtained = false;
};

