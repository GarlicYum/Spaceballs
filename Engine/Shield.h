#pragma once
#include "MainWindow.h"
#include "Graphics.h"

class Shield
{
public:
	void Update(class Ship& ship);
	void Draw(Graphics& gfx);
	void DrawMeter(Graphics& gfx);
	bool GetisActive();
	float GetX();
	float GetY();
	int GetSize();

private:
	float x;
	float y;
	static constexpr int radius = 100;
	bool isActive = true;
	int shieldSize = 0;
	int holeSize = -5;
	int meterWidth = 300;
	static constexpr int meterHeight = 10;
	int meterX = 400;
	int meterY = 570;
	Color c = Colors::Blue;
	int meterCounter = 0;
	static constexpr int meterDecrease = 3;
};