#pragma once
#include "SmallEnemyShip.h"
#include <random>
#include <vector>

class EnemyManager
{
public:
	EnemyManager(const Surface& smallSurface);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt);

private:
	static constexpr int nSmallShipMax = 16;
	int nSmallShip = 2;
	std::vector<SmallEnemyShip> smallShip;
};