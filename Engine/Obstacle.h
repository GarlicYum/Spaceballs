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

private:
	float x = 0.0f;
	float y = -120.0f;
	float vy = 60.0f;
	const Surface& surface;
};