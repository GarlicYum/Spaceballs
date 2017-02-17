#pragma once
#include "RectF.h"
#include "Animation.h"
#include "Vec2.h"


class BlackHole
{
public:
	BlackHole(float X, AnimationFrames& bHoleAnim);
	void Reset();
	void Update(float dt);
	void Draw(Graphics& gfx);
	void HandleCollision();
	RectF GetCollisionRect() const;

private:
	Vec2 pos;
	static constexpr float vy = 80.0f;
	static constexpr float width = 100.0f;
	static constexpr float height = 100.0f;
	Animation bHoleSpin;
};