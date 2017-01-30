#pragma once
#include "Mine.h"
#include <random>

class MineManager
{
public:
	MineManager();
	void Update(Ship& ship);
	void Draw(Graphics & gfx);
private:
	static constexpr int nMinesMax = 130;
	int nMines = 0;
	int mineCounter = 0;
	int newMine = 30;
	Mine mine[nMinesMax];
};