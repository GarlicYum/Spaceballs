#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Sound.h"

class Shield
{
public:
	Shield();
	void Update(class Ship& ship, Sound& shieldon, Sound& shieldoff);
	void Draw(Graphics& gfx);
	void DrawMeter(Graphics& gfx);
	bool GetisActive() const;
	void SetisActive(bool active);
	float GetX();
	float GetY();
	int GetSize();

private:
	float x;
	float y;
	static constexpr int radius = 100;
	bool isActive = false;
	int shieldSize = 0;
	int holeSize = -5;
	int meterWidth;
	static constexpr int meterHeight = 10;
	int meterX = 400;
	int meterY = 570;
	Color c = Colors::Blue;
	int meterCounter = 0;
	static constexpr int meterDecrease = 3;
	bool newShield = true;
};