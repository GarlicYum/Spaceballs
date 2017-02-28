#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include "RectF.h"
#include "Animation.h"
#include "BulletManager.h"
#include "Health.h"

class Boss
{
public:
	enum State
	{
		EntranceState, AliveState, ExplodingState, DeadState
	};
	Boss(AnimationFrames& bossAnim, BulletManager& BulletM);
	void Update(float dt);
	void Draw(Graphics& gfx);
	RectF GetCollisionRect();
	void Attack();
	void Move(float dt);
	void HandleCollision();

private:
	Vec2 pos = Vec2(315.0f, -250.0f);
	Vec2 vel = Vec2(100.0f, 100.0f);
	Vec2 canon;
	static constexpr float entranceSpeed = 50.0f;
	static constexpr float width = 170.0f;
	static constexpr float height = 250.0f;
	static constexpr int collisionDmg = 75;
	static constexpr int bulletDmg = 50;
	Animation bossSprite;
	BulletManager& bulletM;
	State state = EntranceState;

	float bulletTimer = 0.0f;
	static constexpr float newBullet = 1.5f;
	Health health;
};


/*
static constexpr int bulletHalfWidth = 30;
static constexpr int bulletHalfHeight = 37;
static constexpr int bulletRectSize = 15;
static constexpr float bulletVel = -400.0f;
*/
