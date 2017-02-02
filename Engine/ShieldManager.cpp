#include "ShieldManager.h"
#include "Ship.h"

ShieldManager::ShieldManager()
{	
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
	for (int i = 0; i < nSmallMax; i++)
	{
		s_shield[i].SetPos(xDist(rng));
	}	
}

void ShieldManager::Update(Ship & ship, float dt, Sound& shieldon, Sound& shieldoff)
{
	shield.Update(ship, shieldon, shieldoff);

	for (int i = 0; i < nSmall; i++)
	{
		s_shield[i].Update(ship, dt, shield);
	}

	smallCounter++;
	if (smallCounter == newSmall && nSmall != nSmallMax)
	{
		nSmall++;
		smallCounter = 0;
	}
}

void ShieldManager::Draw(Graphics & gfx)
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

