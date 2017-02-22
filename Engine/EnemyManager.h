#pragma once
#include "SmallEnemyShip.h"
#include <random>
#include <vector>

class EnemyManager
{
public:
	EnemyManager(AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, 
		BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt, float playerX);
	int GetSmallCount() const;
	SmallEnemyShip& GetSmallShip(int Idx);
	const SmallEnemyShip& GetSmallShip(int Idx) const;

private:
	static constexpr int nSmallShipMax = 16;
	int nSmallShip = 0;
	float smallShipCounter = 0.0f;
	static constexpr float newSmallShip = 5.5f;
	std::vector<SmallEnemyShip> smallShip;
};