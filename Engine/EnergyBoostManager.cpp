#include "EnergyBoostManager.h"
#include <random>

EnergyBoostManager::EnergyBoostManager(Sound& BoostSound, Surface& BoostSurface)
	:
	boostSound(BoostSound),
	boostSurface(BoostSurface)
{}

void EnergyBoostManager::Update(Ship& ship, float dt)
{
	for (int i = 0; i < nEBoost; ++i)
	{
		eBoost[i].Update(ship, dt);
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

	eBoost.clear();
	nEBoost = 0;
}

void EnergyBoostManager::SpawnEnergyBoost(float X, float Y)
{
	eBoost.push_back(EnergyBoost(X, Y, boostSound, boostSurface));
	nEBoost++;
}
