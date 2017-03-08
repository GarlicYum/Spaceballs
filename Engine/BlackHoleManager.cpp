#include "BlackHoleManager.h"

BlackHoleManager::BlackHoleManager(AnimationFrames & bHoleAnim)
{
//	std::mt19937 rng;
//	std::uniform_real_distribution<float> xDist(0.0f, 750.0f);
//	for (int i = 0; i < nHolesMax; ++i)
		bHole.emplace_back<BlackHole>(BlackHole{ 15.0f, bHoleAnim });
		bHole.emplace_back<BlackHole>(BlackHole{ 15.0f, bHoleAnim });
		bHole.emplace_back<BlackHole>(BlackHole{ 15.0f, bHoleAnim });
		bHole.emplace_back<BlackHole>(BlackHole{ 350.0f, bHoleAnim });
}

void BlackHoleManager::Reset()
{
	nHoles = 0;
	holeCounter = 0;
	for (int i = 0; i < nHolesMax; ++i)
	{
		bHole[i].Reset();
	}
}

void BlackHoleManager::Update(float dt)
{
	if (nHoles != nHolesMax)
	{
		if ((holeCounter += dt) > newHole)
		{
			holeCounter = 0.0f;
			nHoles++;
		}
	}
	
	for (int i = 0; i < nHoles; ++i)
	{
		bHole[i].Update(dt);
	}
}

void BlackHoleManager::Draw(Graphics& gfx)
{
	for (int i = 0; i < nHoles; ++i)
	{
		bHole[i].Draw(gfx);
	}
}

int BlackHoleManager::GetBlackHoleCount() const
{
	return nHoles;
}

BlackHole & BlackHoleManager::GetBlackHole(int Idx)
{
	return bHole[Idx];
}

const BlackHole & BlackHoleManager::GetBlackHole(int Idx) const
{
	return bHole[Idx];
}
