#pragma once
#include "MainWindow.h"
#include "EnergyBoost.h"
#include <vector>

class EnergyBoostManager
{
public:
	EnergyBoostManager(Sound& BoostSound, Surface& BoostSurface);
	void Update(Ship& ship, float dt);
	void Draw(Graphics& gfx, Ship& ship);
	EnergyBoost& GetBoost(int Idx);
	const EnergyBoost& GetBoost(int Idx) const;
	int GetBoostCount() const;
	void Reset();
	void SpawnEnergyBoost(float X, float Y);

private:
	int nEBoost = 0;
	std::vector<EnergyBoost> eBoost;
	Sound& boostSound;
	Surface& boostSurface;
};