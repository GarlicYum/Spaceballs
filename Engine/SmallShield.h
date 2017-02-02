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
	bool DetectCollision(Ship& ship);
	void SetPos(float X);
private:
	float x = 0.0f;
	float y = -40.0f;
	float vy = 4.0f * 60.0f;
	static constexpr int radius = 20;
	static constexpr int hole = 18;
	Color c = Colors::Blue;
	bool isObtained = false;
};

