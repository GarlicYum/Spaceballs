#pragma once
#include "SmallEnemyShip.h"
#include <random>
#include <vector>

class SmallEnemyManager
{
public:
	SmallEnemyManager(AnimationFrames& SmallExhaust, AnimationFrames& SmallExplode, Sound& SmallExplo, 
		BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM, AnimationFrames& bulletAnim, const Surface& ShipFlash);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt, float playerX);
	int GetSmallCount() const;
	SmallEnemyShip& GetSmallShip(int Idx);
	const SmallEnemyShip& GetSmallShip(int Idx) const;
	void SpawnSmallShip(float X, float Y);

private:
	int nSmallShip = 0;
	std::vector<SmallEnemyShip> smallShip;

	Animation bulletSprite;
	AnimationFrames& bulletFrames;
	BulletManager& leftM;
	BulletManager& rightM;
	AnimationFrames& smallExhaust;
	AnimationFrames& smallExplode;
	const Surface& shipFlash;
	Sound& exploSound;
};