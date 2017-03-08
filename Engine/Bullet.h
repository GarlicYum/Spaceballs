#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"
#include "Animation.h"

class Bullet
{
public:
	enum BulletState
	{
		AliveState, DeadState
	};
	Bullet() = default;
	Bullet(Vec2& pos_in);
	Bullet(Vec2& pos_in, Vec2& Vel, int Width, int Height, int bulletRectSize, int Dmg);
	void Update(float dt, Animation& bulletSprite);
	bool HasSpawned() const;
	void Draw(Graphics & gfx, Animation& bulletSprite);
	bool IsActive() const;
	RectF GetCollisionRect() const;
	void HandleCollision();
	int GetDamage();
	int GetBossDmg();
	void Reset();

private:
	BulletState bState = DeadState;
	bool hasSpawned = false;
	Vec2 pos;
	int halfWidth = 20;
	int halfHeight = 25;
	int rectSize = 10;
	Vec2 vel = Vec2(0.0f, 900.0f);
	int dmg = 20;
	int bossDmg = 1;
};