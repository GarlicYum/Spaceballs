#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "RectF.h"

class BigEnemyShip
{
public:
	BigEnemyShip(float X, const Surface& surface);
	void Draw(Graphics& gfx);
	void Update(float dt);

private:
	Vec2 pos;
	Vec2 vel = Vec2(100.0f, 100.0f);
	float resetX;
	const Surface& shipSurface;
};