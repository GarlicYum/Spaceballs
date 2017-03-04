#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "RectF.h"
#include "BulletManager.h"
#include "Timer.h"

class BigEnemyShip
{
public:
	enum State
	{
		WaitState, AliveState, DyingState
	};
	BigEnemyShip(float X, const Surface& surface, BulletManager& BulletM, AnimationFrames& ExploAnim, Sound& ExploSound, AnimationFrames& bulletAnim);
	void Draw(Graphics& gfx);
	void Update(float dt);
	void Reset();
	RectF GetCollisionRect() const;
	int GetCollisionDmg() const;
	int GetBulletDmg() const;
	void HandleCollision(int dmg);
	void Attack(float dt);
	void Move(float dt);
	bool IsAlive() const;

private:
	Vec2 pos;
	Vec2 canon = Vec2(42.5f, 75.0f);
	Vec2 vel = Vec2(100.0f, 100.0f);
	static constexpr float width = 145.0f;
	static constexpr float height = 90.0f;
	float resetX;
	const Surface& shipSurface;
	State state = WaitState;
	BulletManager& bulletM;
	static constexpr int bulletHalfWidth = 30;
	static constexpr int bulletHalfHeight = 37;
	static constexpr int bulletRectSize = 15;
	Vec2 bulletVel = Vec2(0.0f, -400.0f);
	static constexpr int bulletDmg = 50;
	static constexpr int collisionDmg = 75;
	int hp = 600;
	Animation exploAnim;
	Sound& exploSound;
	static constexpr float bulletPitch = 0.3f;
	Timer waitTimer;
	Timer bulletTimer;
	Animation bulletSprite;
};