#pragma once

#include "RectF.h"
#include "Vec2.h"
#include "BulletManager.h"
#include "Graphics.h"

class SmallEnemyShip
{
public:
	enum EnemyState
	{
		AliveState, DyingState, DeadState
	};
	SmallEnemyShip(float x, const Surface& enemySurface);
	void Attack();
	void Move(float dt);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void Reset();

private:
	Vec2 pos;
	float resetX;
	float resetY = -100.0f;
	Vec2 vel;
	BulletManager bulletM;
	EnemyState state;
	const Surface& surface;
};
