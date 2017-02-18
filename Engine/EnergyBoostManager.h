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

private:
	static constexpr int nEBoostMax = 3;
	int nEBoost = 0;
	float eBoostCounter = 0.0f;
	static constexpr float newEBoost = 16.0f;
	std::vector<EnergyBoost> eBoost;
	Sound& boostSound;
	Surface& boostSurface;
};