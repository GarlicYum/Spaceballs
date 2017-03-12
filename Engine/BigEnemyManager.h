#pragma once
#include <vector>
#include "BigEnemyShip.h"
#include "Graphics.h"
#include "Animation.h"

class BigEnemyManager
{
public:
	BigEnemyManager(const Surface& ShipSurface, BulletManager& BulletM, AnimationFrames& ExploAnim, Sound& ExploSound, AnimationFrames& BulletAnim, const Surface& ShipFlash);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void Spawn(float X, float Y);
	BigEnemyShip& GetBigShip(int Idx);
	const BigEnemyShip& GetBigShip(int Idx) const;
	int GetBigCount() const;
	void Reset();

private:
	std::vector<BigEnemyShip>bigEnemy;
	const Surface& shipSurface;
	BulletManager& bulletM;
	AnimationFrames& exploAnim;
	Sound& exploSound;
	AnimationFrames& bulletAnim;
	Animation bulletSprite;
	int nBigEnemy = 0;
	const Surface& shipFlash;
};
