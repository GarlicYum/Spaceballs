#pragma once
#include "MainWindow.h"
#include "EnergyBoost.h"
#include <random>


class EnergyBoostManager
{
public:
	EnergyBoostManager();
	void Update(Ship& ship, float dt);
	void Draw(Graphics & gfx, Ship& ship);
private:
	static constexpr int nEBoostMax = 3;
	int nEBoost = 0;
	int eBoostCounter = 0;
	int newEBoost = 900;
	EnergyBoost eBoost[nEBoostMax];
};
