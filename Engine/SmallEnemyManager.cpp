#include "SmallEnemyManager.h"

SmallEnemyManager::SmallEnemyManager(AnimationFrames& SmallExhaust, AnimationFrames& SmallExplode, Sound& SmallExplo, 
	BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM, AnimationFrames& bulletAnim)
	:
	bulletSprite(bulletAnim, 2),
	leftM(smallLeftBulletM),
	rightM(smallRightBulletM),
	smallExhaust(SmallExhaust),
	smallExplode(SmallExplode),
	exploSound(SmallExplo),
	bulletFrames(bulletAnim)
{
//	std::mt19937 rng;
//	std::uniform_real_distribution<float> xDist(0.0f, 545.0f);
//	for (int i = 0; i < nSmallShipMax; ++i)
//	{
//		smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ xDist(rng), smallexhaust, smallexplode, smallexplo, smallLeftBulletM, smallRightBulletM, bulletAnim });
//	}
}

void SmallEnemyManager::Draw(Graphics & gfx)
{
	leftM.DrawBullets(gfx, bulletSprite);
	rightM.DrawBullets(gfx, bulletSprite);
	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Draw(gfx);
	}
}

void SmallEnemyManager::Reset()
{
	nSmallShip = 0;
//	smallShipCounter = 0.0f;
//	for (int i = 0; i < nSmallShipMax; ++i)
//	{
//		smallShip[i].Reset();
//	}
}

void SmallEnemyManager::Update(float dt, float playerX)
{
	leftM.UpdateBullets(dt, bulletSprite);
	rightM.UpdateBullets(dt, bulletSprite);
//	if ((smallShipCounter += dt) >= newSmallShip && nSmallShip != nSmallShipMax)
//	{
//		smallShipCounter = 0.0f;
//		nSmallShip++;
//	}

	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip[i].Update(dt, playerX);
	}
}

int SmallEnemyManager::GetSmallCount() const
{
	return nSmallShip;
}

SmallEnemyShip & SmallEnemyManager::GetSmallShip(int Idx)
{
	return smallShip[Idx];
}

const SmallEnemyShip & SmallEnemyManager::GetSmallShip(int Idx) const
{
	return smallShip[Idx];
}

void SmallEnemyManager::SpawnSmallShip(float X, float Y)
{
	nSmallShip++;
	smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ X, Y, smallExhaust, smallExplode, exploSound, leftM, rightM});
}
