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
		AliveState, DyingState, DeadState
	};
	BigEnemyShip(float X, float Y, const Surface& surface, BulletManager& BulletM, AnimationFrames& ExploAnim, Sound& ExploSound, const Surface& ShipFlash);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetCollisionRect() const;
	int GetCollisionDmg() const;
	int GetBulletDmg() const;
	void HandleCollision(int dmg);
	void Attack(float dt);
	void Move(float dt);
	bool IsAlive() const;
	bool GetCoolDown() const;

private:
	Vec2 pos;
	Vec2 canon = Vec2(42.5f, 75.0f);
	Vec2 vel = Vec2(100.0f, 200.0f);
	static constexpr float width = 145.0f;
	static constexpr float height = 90.0f;
	const Surface& shipSurface;
	State state = AliveState;
	BulletManager& bulletM;
	static constexpr int bulletHalfWidth = 30;
	static constexpr int bulletHalfHeight = 37;
	static constexpr int bulletRectSize = 15;
	Vec2 bulletVel = Vec2(0.0f, -400.0f);
	static constexpr int bulletDmg = 50;
	static constexpr int collisionDmg = 75;
	int hp = 20;
	Animation exploAnim;
	Sound& exploSound;
	static constexpr float bulletPitch = 0.3f;
	Timer bulletTimer;
	Timer timer;
	Timer coolDownTimer;
	Timer hitTimer;
	bool isHit = false;
	bool coolDown = false;
	const Surface& shipFlash;
};