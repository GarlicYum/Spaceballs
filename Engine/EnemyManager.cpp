#include "EnemyManager.h"

EnemyManager::EnemyManager(const Surface & smallSurface, AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 545.0f);
	for (int i = 0; i < nSmallShipMax; ++i)
	{
		smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ xDist(rng), smallSurface, smallexhaust, smallexplode, smallexplo });
	}
}

void EnemyManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Draw(gfx);
	}
}

void EnemyManager::Reset()
{
	nSmallShip = 0;
	smallShipCounter = 0.0f;
	for (int i = 0; i < nSmallShipMax; ++i)
	{
		smallShip[i].Reset();
	}
}

void EnemyManager::Update(float dt)
{
	if ((smallShipCounter += dt) >= newSmallShip && nSmallShip != nSmallShipMax)
	{
		smallShipCounter = 0.0f;
		nSmallShip++;
	}

	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Update(dt);
	}
}

int EnemyManager::GetSmallCount() const
{
	return nSmallShip;
}

SmallEnemyShip & EnemyManager::GetSmallShip(int Idx)
{
	return smallShip[Idx];
}

const SmallEnemyShip & EnemyManager::GetSmallShip(int Idx) const
{
	return smallShip[Idx];
}
