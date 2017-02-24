#pragma once

#include "blackhole.h"
#include <vector>
#include <random>

class BlackHoleManager
{
public:
	BlackHoleManager(AnimationFrames& bHoleAnim);
	void Reset();
	void Update(float dt);
	void Draw(Graphics& gfx);
	int GetBlackHoleCount() const;
	BlackHole& GetBlackHole(int Idx);
	const BlackHole& GetBlackHole(int Idx) const;

private:
	static constexpr int nHolesMax = 1;
	int nHoles = 0;
	float holeCounter = 0.0f;
	static constexpr float newHole = 3.5f;
	std::vector<BlackHole> bHole;
};