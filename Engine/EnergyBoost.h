#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"

class EnergyBoost
{
public:
	void Draw(Graphics& gfx);
	bool DetectCollision(Ship& ship);
	void Update(Ship& ship, float dt);
	void SetPos(float X);

private:
	float x = 0.0f;
	float y = 40.0f;
	float vy = 4.0f * 60.0f;
	bool isObtained = false;
	bool isRestored = false;
	static constexpr float width = 40.0f;
	static constexpr float height = 32.0f;
	static constexpr int restoreAmount = 150;
};
