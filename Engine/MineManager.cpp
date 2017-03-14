#include "MineManager.h"
#include "Ship.h"

MineManager::MineManager(Sound& Explosion, const Surface& MineSurface, AnimationFrames& ExplosionFrames)
	:
	explosion(Explosion),
	mineSurface(MineSurface),
	exploFrames(ExplosionFrames)
{}

void MineManager::Update(float Dt)
{
	for (int i = 0; i < nMines; ++i)
	{
		mine[i].Update(Dt);
	}
}

void MineManager::Draw(Graphics& gfx)
{
	for (int i = 0; i < nMines; ++i)
	{
		mine[i].Draw(gfx);
	}
}

void MineManager::SpawnMine(float X, float Y)
{
	nMines++;
	mine.emplace_back<Mine>(Mine{ X, Y, mineSurface, explosion, exploFrames });
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
	for (int i = 0; i < nMines; ++i)
	{
		mine.pop_back();
	//	mine[i].Reset();
	}
	nMines = 0;
}
