#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"

class Bullet
{
public:
	enum BulletState
	{
		AliveState, DeadState
	};
	Bullet() = default;
	Bullet(Vec2& pos_in);
	void Update(float dt);
	bool HasSpawned() const;
	void Draw(Graphics & gfx);
	bool IsActive() const;
	RectF GetCollisionRect() const;
	void HandleCollision();
	int GetDamage();
	void Reset();

private:
	BulletState bState = DeadState;
	bool hasSpawned = false;
	Vec2 pos;
	static constexpr int bulletSize = 10;
	static constexpr float vy = 15.0f * 60.0f;
	static constexpr int dmg = 20;
};