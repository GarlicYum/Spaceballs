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
	void Update();
	void Draw(Graphics& gfx);
	void Reset();

private:
	Vec2 pos;
	Vec2 vel;
	BulletManager bulletM;
	EnemyState state;
	const Surface& surface;
};
