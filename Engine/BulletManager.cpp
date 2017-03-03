#include "BulletManager.h"
#include "Graphics.h"

const Bullet & BulletManager::GetBullet(int Idx) const
{
	return bullets[Idx];
}

Bullet& BulletManager::GetBullet(int Idx)
{
	return bullets[Idx];
}

int BulletManager::GetNumBullets() const
{
	return nBullets;
}

void BulletManager::FireBullet(Vec2& canonPos)
{
	if (shotsFired == false)
	{
		for (int i = 0; i < nBullets; ++i)
		{
			auto& bullet = bullets[i];
			if (!bullet.HasSpawned())
			{
				bullet = Bullet(canonPos);
				gun.Play(0.5f, 0.5f);
				shotsFired = true;
				break;
			}
		}
	}
}

void BulletManager::FireBullet(Vec2& canonPos, Vec2& vel, int bulletWidth, int bulletHeight, int bulletRectSize, int Dmg, float pitch)
{
	if (shotsFired == false)
	{
		for (int i = 0; i < nBullets; ++i)
		{
			auto& bullet = bullets[i];
			if (!bullet.HasSpawned())
			{
				bullet = Bullet(canonPos, vel, bulletWidth, bulletHeight, bulletRectSize, Dmg);
				gun.Play(pitch, 0.5f);
				shotsFired = true;
				break;
			}
		}
	}
}

void BulletManager::UpdateBullets(float Dt, Animation& bulletSprite)
{
	for (int i = 0; i < nBullets; ++i)
	{
		auto &bullet = bullets[i];
		if (bullet.HasSpawned())
		{
			bullet.Update(Dt, bulletSprite);
		}
	}
}

void BulletManager::DrawBullets(Graphics& Gfx, Animation& bulletSprite)
{
	for (int i = 0; i < nBullets; ++i)
	{
		auto& bullet = bullets[i];
		if (bullet.HasSpawned())
		{
			bullet.Draw(Gfx, bulletSprite);
		}
	}
}

void BulletManager::Reset()
{
	for (int i = 0; i < nBullets; ++i)
	{
		bullets[i].Reset();
	}
}

void BulletManager::ResetShotsFired()
{
	shotsFired = false;
}