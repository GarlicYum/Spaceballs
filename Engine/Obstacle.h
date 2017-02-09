#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "RectF.h"
#include "Ship.h"

class Obstacle
{
public:
	Obstacle(float X, const Surface& obstacleSurface);
	void Draw(Graphics& gfx);
	void Update(float dt);
	void HandleCollision(Ship& ship);
	RectF GetCollisionRect();

private:
	float x = 0.0f;
	float y = -120.0f;
	float vy = 120.0f;
	static constexpr float width = 255;
	static constexpr float height = 115;
	const Surface& surface;
};