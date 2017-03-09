#pragma once
#include "SmallEnemyShip.h"
#include <random>
#include <vector>

class SmallEnemyManager
{
public:
	SmallEnemyManager(AnimationFrames& SmallExhaust, AnimationFrames& SmallExplode, Sound& SmallExplo, 
		BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM, AnimationFrames& bulletAnim);
	void Draw(Graphics& gfx);
	void Reset();
	void Update(float dt, float playerX);
	int GetSmallCount() const;
	SmallEnemyShip& GetSmallShip(int Idx);
	const SmallEnemyShip& GetSmallShip(int Idx) const;
	void SpawnSmallShip(float X, float Y);

private:
//	static constexpr int nSmallShipMax = 16;
	int nSmallShip = 0;
//	float smallShipCounter = 0.0f;
//	static constexpr float newSmallShip = 6.0f;
	std::vector<SmallEnemyShip> smallShip;

	Animation bulletSprite;
	AnimationFrames& bulletFrames;
	BulletManager& leftM;
	BulletManager& rightM;
	AnimationFrames& smallExhaust;
	AnimationFrames& smallExplode;
	Sound& exploSound;
};