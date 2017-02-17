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

void BulletManager::FireBullet(Vec2& canonPos, float Dt)
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

void BulletManager::UpdateBullets(float Dt)
{
	for (int i = 0; i < nBullets; ++i)
	{
		auto &bullet = bullets[i];
		if (bullet.HasSpawned())
		{
			bullet.Update(Dt);
		}
	}
}

void BulletManager::DrawBullets(Graphics& Gfx)
{
	for (int i = 0; i < nBullets; ++i)
	{
		auto& bullet = bullets[i];
		if (bullet.HasSpawned())
		{
			bullet.Draw(Gfx);
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