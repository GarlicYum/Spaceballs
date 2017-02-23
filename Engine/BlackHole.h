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
	RectF GetCollisionRect() const;
	bool GetIsActive() const;
	void Deactivate();
	void StopVy();
	void StartVy();

private:
	Vec2 pos;
	float vy = 80.0f;
	static constexpr float resetVy = 80.0f;
	static constexpr float width = 100.0f;
	static constexpr float height = 100.0f;
	static constexpr float range = 250.0f;
	Animation bHoleSpin;
	bool isActive = true;
};