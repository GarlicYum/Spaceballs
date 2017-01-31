#include "EnergyBoostManager.h"

EnergyBoostManager::EnergyBoostManager()
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
	for (int i = 0; i < nEBoostMax; i++)
	{
		eBoost[i].SetPos(xDist(rng));
	}
}

void EnergyBoostManager::Update(Ship& ship, float dt)
{
	for (int i = 0; i < nEBoost; i++)
	{
		eBoost[i].Update(ship, dt);
	}

	eBoostCounter++;
	if (eBoostCounter == newEBoost && nEBoost != nEBoostMax)
	{
		nEBoost++;
		eBoostCounter = 0;
	}
}

void EnergyBoostManager::Draw(Graphics & gfx, Ship& ship)
{
	for (int i = 0; i < nEBoost; i++)
	{
		eBoost[i].Draw(gfx);
	}
}