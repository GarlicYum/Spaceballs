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

private:
	static constexpr int nHolesMax = 3;
	int nHoles = 0;
	int holeCounter = 0;
	static constexpr int newHole = 700;
	std::vector<BlackHole> bHole;
};