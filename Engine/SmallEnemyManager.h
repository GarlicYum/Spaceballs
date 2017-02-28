#pragma once
#include "SmallEnemyShip.h"
#include <random>
#include <vector>

class SmallEnemyManager
{
public:
	SmallEnemyManager(AnimationFrames& smallexhaust, AnimationFrames& smallexplode, Sound& smallexplo, 
		BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM, AnimationFrames& bulletAnim);
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
	static constexpr float newSmallShip = 6.0f;
	std::vector<SmallEnemyShip> smallShip;

	Animation bulletSprite;
	BulletManager& leftM;
	BulletManager& rightM;
};