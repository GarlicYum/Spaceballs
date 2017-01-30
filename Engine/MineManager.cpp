#include "MineManager.h"

MineManager::MineManager()
{
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist(0, 700);
	for (int i = 0; i < nMinesMax; i++)
	{
		mine[i].SetPos(xDist(rng));
	}
}

void MineManager::Update(Ship& ship)
{
	for (int i = 0; i < nMines; i++)
	{
		if (mine[i].isActive())
		mine[i].Update(ship);
	}

	mineCounter++;
	if (mineCounter == newMine && nMines != nMinesMax)
	{
		nMines++;
		mineCounter = 0;
	}
}

void MineManager::Draw(Graphics & gfx)
{
	for (int i = 0; i < nMines; i++)
	{
		mine[i].Draw(gfx);
	}
}
