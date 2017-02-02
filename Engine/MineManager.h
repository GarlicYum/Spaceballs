#pragma once
#include "MainWindow.h"
#include "Mine.h"
#include <random>
#include "ShieldManager.h"


class MineManager
{
public:
	MineManager();
	void Update(Ship& ship, float dt, ShieldManager shieldM);
	void Draw(Graphics & gfx, Ship& ship);

private:
	static constexpr int nMinesMax = 130;
	int nMines = 0;
	int mineCounter = 0;
	int newMine = 30;
	Mine mine[nMinesMax];
};