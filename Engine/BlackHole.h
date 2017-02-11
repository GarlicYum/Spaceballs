#pragma once
#include "RectF.h"
#include "Animation.h"


class BlackHole
{
public:
	BlackHole(float X, AnimationFrames& bHoleAnim);
	void Reset();
	void Update(float dt);
	void Draw(Graphics& gfx);

private:
	float x;
	float y = -50.0f;
	static constexpr float vy = 80.0f;
	Animation bHoleSpin;
};