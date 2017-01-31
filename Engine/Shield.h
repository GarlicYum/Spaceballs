#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "Ship.h"

class Shield
{
public:
	void Update(Ship& ship);
	void Draw();
private:
	float x;
	float y;
	static constexpr int radius = 100;
	bool isObtained = false;

};