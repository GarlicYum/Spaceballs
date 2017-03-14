#include "SmallEnemyManager.h"

SmallEnemyManager::SmallEnemyManager(AnimationFrames& SmallExhaust, AnimationFrames& SmallExplode, Sound& SmallExplo, 
	BulletManager& smallLeftBulletM, BulletManager& smallRightBulletM, AnimationFrames& bulletAnim, const Surface& ShipFlash)
	:
	bulletSprite(bulletAnim, 2),
	leftM(smallLeftBulletM),
	rightM(smallRightBulletM),
	smallExhaust(SmallExhaust),
	smallExplode(SmallExplode),
	exploSound(SmallExplo),
	bulletFrames(bulletAnim),
	shipFlash(ShipFlash)
{}

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
	for (int i = 0; i < nSmallShip; ++i)
	{
		smallShip.pop_back();
	//	smallShip[i].Reset();
	}
	nSmallShip = 0;
}

void SmallEnemyManager::Update(float dt, float playerX)
{
	leftM.UpdateBullets(dt, bulletSprite);
	rightM.UpdateBullets(dt, bulletSprite);

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
	smallShip.emplace_back<SmallEnemyShip>(SmallEnemyShip{ X, Y, smallExhaust, smallExplode, exploSound, leftM, rightM, shipFlash});
}
