#pragma once

#include "RectF.h"
#include "Vec2.h"
#include "BulletManager.h"
#include "Graphics.h"
#include "Animation.h"

class SmallEnemyShip
{
public:
	enum EnemyState
	{
		AliveState, DyingState, DeadState
	};
	SmallEnemyShip(float x, const Surface& enemySurface, AnimationFrames& smallexhaust);
	void Attack();
	void MoveY(float dt);
	void MoveX(float dt);
	void Update(float dt);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect() const;
	void Reset();
	void HandleCollision(int dmg);
	int GetCollisionDmg() const;
	bool IsDead() const;
	bool GetCoolDown() const;

private:
	bool coolDown = false;
	static constexpr float coolDownOver = .5f;
	float coolDownTime = 0.0f;
	Vec2 pos;
	float resetX;
	float resetY = -100.0f;
	Vec2 vel = Vec2(200.0f, 200.0f);
	BulletManager bulletM;
	const Surface& surface;
	int hp = 80;
	static constexpr float width = 90.0f;
	static constexpr float height = 70.0f;
	static constexpr int collisionDmg = 50;
	EnemyState state = AliveState;
	Animation smallExhaust;
};
