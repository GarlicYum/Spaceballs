#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"
#include "Sound.h"
#include "Vec2.h"

class EnergyBoost
{
public:
	EnergyBoost(float X, Sound& BoostSound, Surface& BoostSurface);
	void Update(Ship& ship, float dt);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect() const;
	void HandleCollision(Ship& ship);
	void Reset();

private:
	Vec2 pos;
	static constexpr float resetY = -40.0f;
	static constexpr float vy = 4.0f * 60.0f;
	bool isObtained = false;
	bool isRestored = false;
	static constexpr float width = 40.0f;
	static constexpr float height = 32.0f;
	static constexpr int restoreAmount = 150;
	Surface& heart;
	Sound& boostSound;
};
