#pragma once
#include "RectF.h"
#include "Animation.h"
#include "Vec2.h"


class BlackHole
{
public:
	BlackHole(float X, float Y, AnimationFrames& bHoleAnim);
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
	Vec2 resetPos;
	float vy = 200.0f;
	static constexpr float width = 100.0f;
	static constexpr float height = 100.0f;
	static constexpr float range = 250.0f;
	Animation bHoleSpin;
	bool isActive = true;
};