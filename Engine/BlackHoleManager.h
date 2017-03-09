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
	void SpawnBlackHole(float X, float Y);
	int GetBlackHoleCount() const;
	BlackHole& GetBlackHole(int Idx);
	const BlackHole& GetBlackHole(int Idx) const;

private:
	int nHoles = 0;
	std::vector<BlackHole> bHole;
	AnimationFrames& blackHoleAnim;
};