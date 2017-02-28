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
	Bullet(Vec2& pos_in, float VY, Color C, int bulletsize, int Dmg);
	void Update(float dt, Animation& bulletSprite);
	bool HasSpawned() const;
	void Draw(Graphics & gfx, Animation& bulletSprite);
	bool IsActive() const;
	RectF GetCollisionRect() const;
	void HandleCollision();
	int GetDamage();
	void Reset();

private:
	BulletState bState = DeadState;
	bool hasSpawned = false;
	Vec2 pos;
	int bulletWidth = 40;
	int bulletHeight = 50;
	float vy = 15.0f * 60.0f;
	int dmg = 20;
	Color color = Colors::Magenta;
};