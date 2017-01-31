#pragma once
#include "Graphics.h"
#include "Ship"

class Shield
{
public:
	void Update(Ship& ship);
	void Draw();
private:
	int x;
	int y;
	static constexpr int radius = 100;
	bool isObtained = false;

};