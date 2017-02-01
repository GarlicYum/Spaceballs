#pragma once
#include "MainWindow.h"
#include "Ship.h"
#include "Shield.h"
#include "Graphics.h"
#include <random>


class ShieldManager
{
public:
	ShieldManager();
	void Update(Ship& ship);
	void Draw(Graphics& gfx);
	Shield& GetShield();
private:
	Shield shield;
};