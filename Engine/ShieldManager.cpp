#include "ShieldManager.h"
#include "Ship.h"

ShieldManager::ShieldManager()
{}

void ShieldManager::Update(Ship & ship, float dt, Sound& shieldon, Sound& shieldoff)
{
	shield.Update(ship, shieldon, shieldoff);

	for (int i = 0; i < nSmall; i++)
	{
		s_shield[i].Update(ship, dt, shield);
	}
}

void ShieldManager::Draw(Graphics& gfx)
{
	shield.Draw(gfx);

	for (int i = 0; i < nSmall; i++)
	{
		s_shield[i].Draw(gfx);
	}
}

Shield & ShieldManager::GetShield()
{
	return shield;
}

int ShieldManager::GetShieldCount() const
{
	return nSmall;
}

SmallShield& ShieldManager::GetSmallShield(int Idx)
{
	return s_shield[Idx];
}

const SmallShield& ShieldManager::GetSmallShield(int Idx) const
{
	return s_shield[Idx];
}

void ShieldManager::Reset()
{
	for (int i = 0; i < nSmall; ++i)
	{
		s_shield.pop_back();
	//	s_shield[i].Reset();
	}
	nSmall = 0;
	shield.Reset();
}

void ShieldManager::SpawnShield(float X, float Y)
{
	nSmall++;
	s_shield.emplace_back<SmallShield>(SmallShield{ X, Y });
}