#include "MineManager.h"

MineManager::MineManager()
{
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist(0, 750);
	for (int i = 0; i < nMinesMax; i++)
	{
		mine[i].SetPos(xDist(rng));
	}
}

void MineManager::Update()
{
	for (int i = 0; i < nMines; i++)
	{
		mine[i].Update();
	}

	mineCounter++;
	if (mineCounter == newMine)
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
