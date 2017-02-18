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
	int GetShieldCount() const;
	SmallShield& GetSmallShield(int Idx);
	const SmallShield& GetSmallShield(int Idx) const;
	void Reset();

private:
	void SpawnShieldPowerup(float dt);
private:
	static constexpr int nSmallMax = 2;
	Shield shield;
	SmallShield s_shield[nSmallMax];
 	int nSmall = 0;
 	float smallCounter = 0.0f;
 	static constexpr float newSmall = 19.5f;
};

