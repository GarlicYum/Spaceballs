#include "ShieldManager.h"
#include "Ship.h"

ShieldManager::ShieldManager()
{	
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 700.0f);
//	for (int i = 0; i < nShieldMax; i++)
//	{
//		smallShield[i].SetPos(xDist(rng));
//	}	
}

void ShieldManager::Update(Ship & ship)
{
	shield.Update(ship);
}

void ShieldManager::Draw(Graphics & gfx)
{
	shield.Draw(gfx);
}

Shield& ShieldManager::GetShield()
{
	return shield;
}