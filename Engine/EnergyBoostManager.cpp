#include "EnergyBoostManager.h"
#include <random>

EnergyBoostManager::EnergyBoostManager(Sound& BoostSound, Surface& BoostSurface)
	:
	boostSound(BoostSound),
	boostSurface(BoostSurface)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
	for (int i = 0; i < nEBoostMax; ++i)
	{
		eBoost.push_back(EnergyBoost(xDist(rng), boostSound, boostSurface));
	}
}

void EnergyBoostManager::Update(Ship& ship, float dt)
{
	for (int i = 0; i < nEBoost; ++i)
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

void EnergyBoostManager::Draw(Graphics& gfx, Ship& ship)
{
	for (int i = 0; i < nEBoost; ++i)
	{
		eBoost[i].Draw(gfx);
	}
}

EnergyBoost& EnergyBoostManager::GetBoost(int Idx)
{
	return eBoost[Idx];
}

const EnergyBoost& EnergyBoostManager::GetBoost(int Idx) const
{
	return eBoost[Idx];
}

int EnergyBoostManager::GetBoostCount() const
{
	return nEBoost;
}

void EnergyBoostManager::Reset()
{
	nEBoost = 0;
	eBoostCounter = 0;
	for (int i = 0; i < nEBoostMax; ++i)
	{
		eBoost[i].Reset();
	}
}
