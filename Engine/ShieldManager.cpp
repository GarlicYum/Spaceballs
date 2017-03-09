#include "ShieldManager.h"
#include "Ship.h"

ShieldManager::ShieldManager()
{	
//	std::mt19937 rng;
//	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
//	for (int i = 0; i < nSmallMax; i++)
//	{
//		s_shield[i].SetPos(xDist(rng));
//	}	

}

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
		s_shield[i].Reset();
	}
	shield.Reset();
}

void ShieldManager::SpawnShield(float X, float Y)
{
//	if ((smallCounter += dt) > newSmall && nSmall != nSmallMax)
//	{
//		nSmall++;
//		smallCounter = 0.0f;
//	}

	nSmall++;
	s_shield.emplace_back<SmallShield>(SmallShield{ X, Y });
}