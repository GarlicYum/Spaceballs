#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"
#include "Health.h"
#include "Sound.h"

class Mine
{
public:
	bool DetectCollision(Ship& ship);
	void Update(Ship& ship);
	void Draw(Graphics& gfx);
	void SetPos(int X);
	bool isActive();
private:
	int x = 0;
	int y = 0;
	int vy = 7;
	int explosionCounter = 0;
	static constexpr int explosionEnd = 30;
	bool isDetonated = false;
	bool gotPosition = false;
	static constexpr int damage = 40;
	static constexpr int width = 50;
	static constexpr int height = 50;
	bool isDamaged = false;
	Sound explosion = L"explo.wav";
};