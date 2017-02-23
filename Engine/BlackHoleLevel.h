#pragma once
#include "Graphics.h"
#include "Animation.h"
#include "RectF.h"

class BlackHoleLevel
{
public:
	BlackHoleLevel(AnimationFrames& background);
	void Draw(Graphics& gfx);
	void Update();
	RectF GetCollisionRect();

private:
	Animation backGround;
	Vec2 holePos = Vec2(380.0f, 200.0f);
	static constexpr float dimension = 40.0f;
};