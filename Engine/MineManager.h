#pragma once
#include "MainWindow.h"
#include "Mine.h"
#include <random>


class MineManager
{
public:
	MineManager();
	void Update(Ship& ship, float dt);
	void Draw(Graphics & gfx, Ship& ship);
	bool WasHit();

private:
	static constexpr int nMinesMax = 130;
	int nMines = 0;
	int mineCounter = 0;
	int newMine = 30;
	bool wasHit = false;
	Mine mine[nMinesMax];
};