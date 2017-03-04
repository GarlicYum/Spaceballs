#pragma once
#include "Graphics.h"
#include "Animation.h"
#include "RectF.h"
#include "Comet.h"
#include <random>
#include <vector>

class BlackHoleLevel
{
public:
	BlackHoleLevel(AnimationFrames& background, AnimationFrames& cometAnim);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetCollisionRect();
	Comet& GetComet(int Idx);
	const Comet& GetComet(int Idx) const;
	int GetCometCount() const;
	void Reset();

private:
	Animation backGround;
	Vec2 holePos = Vec2(380.0f, 200.0f);
	static constexpr float dimension = 40.0f;
	static constexpr int nCometsMax = 10;
	int nComets = 0;
	float cometTimer = 0.0f;
	static constexpr float newComet = 0.25f;
	std::vector<Comet> comet;
};