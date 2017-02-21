#include "EnemyManager.h"

EnemyManager::EnemyManager(const Surface & smallSurface)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 545.0f);
	for (int i = 0; i < nSmallShipMax; ++i)
	{
		smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ xDist(rng), smallSurface });
	}
}

void EnemyManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Draw(gfx);
	}
}
