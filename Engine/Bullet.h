#pragma once
#include "Graphics.h"
#include "RectF.h"

class Bullet
{
public:
	enum BulletState
	{
		AliveState, DeadState
	};
	Bullet() = default;
	Bullet(float X, float Y);
	void Update(float dt);
	bool HasSpawned() const;
	void Draw(Graphics & gfx);
	bool IsActive() const;
	RectF GetCollisionRect() const;
	void HandleCollision();
	int GetDamage();

private:
	BulletState bState = DeadState;
	bool hasSpawned = false;
	float x;
	float y;
	static constexpr int bulletSize = 10;
	static constexpr float vy = 15.0f * 60.0f;
	static constexpr int dmg = 20;
};