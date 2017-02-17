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
	void HandleBottomCollision(Ship& ship);
	void HandleTopCollision(Ship& ship);
	void HandleLeftCollision(Ship& ship);
	void HandleRightCollision(Ship& ship);
	RectF GetBottomCollisionRect() const;
	RectF GetLeftCollisionRect() const;
	RectF GetRightCollisionRect() const;
	RectF GetTopCollisionRect() const;
	void Reset();

private:
	Vec2 pos;
	static constexpr float resetY = -120.0f;
	float vy = 120.0f;
	static constexpr float width = 255;
	static constexpr float height = 115;
	const Surface& surface;
};