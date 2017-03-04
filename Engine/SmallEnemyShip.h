#pragma once

#include "RectF.h"
#include "Vec2.h"
#include "BulletManager.h"
#include "Graphics.h"
#include "Animation.h"
#include "Timer.h"

class SmallEnemyShip
{
public:
	enum EnemyState
	{
		AliveState, DyingState, DeadState
	};
	SmallEnemyShip(float x, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, 
		BulletManager& smallLeftmanager, BulletManager& smallRightManager, AnimationFrames& bulletAnim);
	void Attack(float dt);
	void Move(float dt, float playerX);
	void Update(float dt, float playerX);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect() const;
	void Reset();
	void HandleCollision(int dmg);
	int GetCollisionDmg() const;
	bool IsAlive() const;
	bool GetCoolDown() const;

private:
	bool coolDown = false;
	Vec2 pos;
	Vec2 leftCanon = Vec2(-9.0f, 30.0f);
	Vec2 rightCanon = Vec2(68.0f, 30.0f);
	float resetX;
	Vec2 vel = Vec2(200.0f, 100.0f);
	BulletManager bulletM;
	int hp = 80;
	static constexpr float width = 90.0f;
	static constexpr float height = 70.0f;
	static constexpr int collisionDmg = 50;
	EnemyState state = AliveState;
	Animation smallExhaust;
	Animation smallExplode;
	Sound& smallExploSound;
	BulletManager& smallLeftM;
	BulletManager& smallRightM;
	static constexpr int bulletDmg = 25;
	Vec2 bulletVel = Vec2(0.0f, -600.0f);
	static constexpr int bulletHalfWidth = 15;
	static constexpr int bulletHalfHeight = 20;
	static constexpr int bulletRectSize = 10;
	static constexpr float bulletPitch = 0.7f;
	Timer bulletTimer;
	Timer coolDownTimer;
};
