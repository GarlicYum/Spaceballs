#pragma once
#include "MainWindow.h"
#include "Ship.h"
#include "Shield.h"
#include "SmallShield.h"
#include "Graphics.h"
#include <random>
#include <vector>

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
	void SpawnShield(float X, float Y);
	
private:
	Shield shield;
	std::vector<SmallShield>s_shield;
 	int nSmall = 0;
};

