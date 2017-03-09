#pragma once
#include "Graphics.h"
#include "Animation.h"
#include "RectF.h"
#include "Comet.h"
#include <random>
#include <vector>
#include "Timer.h"

class BlackHoleLevel
{
public:
	BlackHoleLevel(AnimationFrames& background, AnimationFrames& CometAnim);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetCollisionRect();
	Comet& GetComet(int Idx);
	const Comet& GetComet(int Idx) const;
	int GetCometCount() const;
	void Reset();
	void Spawn(float X, float Y);

private:
	Animation backGround;
	Vec2 holePos = Vec2(380.0f, 200.0f);
	static constexpr float dimension = 40.0f;
	int nComets = 0;
	std::vector<Comet> comet;
	AnimationFrames& cometAnim;
};