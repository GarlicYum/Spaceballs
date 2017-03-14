#include "BlackHoleManager.h"

BlackHoleManager::BlackHoleManager(AnimationFrames & bHoleAnim)
	:
	blackHoleAnim(bHoleAnim)
{}

void BlackHoleManager::Reset()
{
	for (int i = 0; i < nHoles; ++i)
	{
		bHole.pop_back();
	//	bHole[i].Reset();
	}
	nHoles = 0;
}

void BlackHoleManager::Update(float dt)
{
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

void BlackHoleManager::SpawnBlackHole(float X, float Y)
{
	nHoles++;
	bHole.emplace_back<BlackHole>(BlackHole{ X, Y, blackHoleAnim });
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
