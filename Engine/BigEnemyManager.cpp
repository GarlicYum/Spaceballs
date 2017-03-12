#include "BigEnemyManager.h"

BigEnemyManager::BigEnemyManager(const Surface & ShipSurface, BulletManager & BulletM, AnimationFrames & ExploAnim, Sound & ExploSound, 
	AnimationFrames & BulletAnim, const Surface& ShipFlash)
	:
	shipSurface(ShipSurface),
	bulletM(BulletM),
	exploAnim(ExploAnim),
	exploSound(ExploSound),
	bulletAnim(BulletAnim),
	bulletSprite(bulletAnim, 2.0f),
	shipFlash(ShipFlash)
{}

void BigEnemyManager::Update(float dt)
{
	bulletM.UpdateBullets(dt, bulletSprite);
	for (int i = 0; i < nBigEnemy; i++)
	{
		bigEnemy[i].Update(dt);
	}
}

void BigEnemyManager::Draw(Graphics & gfx)
{
	bulletM.DrawBullets(gfx, bulletSprite);
	for (int i = 0; i < nBigEnemy; i++)
	{
		bigEnemy[i].Draw(gfx);
	}
}

void BigEnemyManager::Spawn(float X, float Y)
{
	nBigEnemy++;
	bigEnemy.emplace_back<BigEnemyShip>(BigEnemyShip{ X, Y, shipSurface, bulletM, exploAnim, exploSound, shipFlash });
}

BigEnemyShip & BigEnemyManager::GetBigShip(int Idx)
{
	return bigEnemy[Idx];
}

const BigEnemyShip & BigEnemyManager::GetBigShip(int Idx) const
{
	return bigEnemy[Idx];
}

int BigEnemyManager::GetBigCount() const
{
	return nBigEnemy;
}

void BigEnemyManager::Reset()
{
	for (int i = 0; i < nBigEnemy; ++i)
	{
		bigEnemy[i].Reset();
	}
}
