#pragma once
#include "Graphics.h"
#include "Keyboard.h"
#include "Health.h"
#include "RectF.h"
#include "Sound.h"
#include "Shield.h"
#include "ShieldManager.h"
#include "Animation.h"
#include "Vec2.h"


class Mine
{
public:
	enum MineState
	{
		ActiveState, DetonateState, InActiveState
	};
	Mine(float X, const Surface& MineSurface, Sound& Explosion, AnimationFrames& Anim);
	void HandleCollision(int dmg);
	void Update(float Dt);
	void Draw(Graphics& gfx);
	int GetDamageCost() const;
	void SetState(MineState State);
	RectF GetCollisionRect() const;
	bool IsActive() const;
	void Reset();

private:
	static constexpr int explDamage = 75;
	static constexpr float width = 50.0f;
	static constexpr float height = 50.0f;
	Vec2 pos;
	static constexpr float resetY = -50.0f;
	static constexpr float vy = 5.0f * 60.0f;
	MineState mState = ActiveState;
	const Surface& surface;
	Sound& explosion;
	Animation explo;
	bool gotPosition = false;
	int damage = 0;
	int hp = 60;
};