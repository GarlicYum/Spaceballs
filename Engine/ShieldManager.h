#pragma once
#include "MainWindow.h"
#include "Ship.h"
#include "Shield.h"
#include "SmallShield.h"
#include "Graphics.h"
#include <random>


class ShieldManager
{
public:
	ShieldManager();
	void Update(Ship& ship, float dt, Sound& shieldon, Sound& shieldoff);
	void Draw(Graphics& gfx);
	Shield& GetShield();
private:
	static constexpr int nSmallMax = 2;
	Shield shield;
	SmallShield s_shield[nSmallMax];
	int nSmall = 0;
	int smallCounter = 0;
	int newSmall = 1150;
};

