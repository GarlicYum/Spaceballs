#include "MineManager.h"
#include "Ship.h"

MineManager::MineManager(Sound& Explosion, const Surface& MineSurface, AnimationFrames& ExplosionFrames)
{
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist(0.0f, 750.0f);
	for (int i = 0; i < nMinesMax; ++i)
	{
		mine.emplace_back<Mine>(Mine{ xDist(rng), MineSurface, Explosion, ExplosionFrames });
	}
}

void MineManager::Update(float Dt)
{
	for (int i = 0; i < nMines; ++i)
	{
		mine[i].Update(Dt);
	}

	SpawnMine(Dt);
}

void MineManager::Draw(Graphics& gfx)
{
	for (int i = 0; i < nMines; ++i)
	{
		mine[i].Draw(gfx);
	}
}

void MineManager::SpawnMine(float Dt)
{
	if ((mineCounter += Dt) > newMine && nMines != nMinesMax)
	{
		nMines++;
		mineCounter = 0.0f;
	}
}

Mine& MineManager::GetMine(int Idx)
{
	return mine[Idx];
}

const Mine& MineManager::GetMine(int Idx) const
{
	return mine[Idx];
}

int MineManager::GetMineCount() const
{
	return nMines;
}

void MineManager::Reset()
{
	nMines = 0;
	mineCounter = 0;
	for (int i = 0; i < nMinesMax; ++i)
	{
		mine[i].Reset();
	}
}
