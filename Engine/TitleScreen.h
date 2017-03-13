#pragma once
#include "Graphics.h"

class TitleScreen
{
public:
	void DrawNormal(Graphics& gfx);
	void DrawEasy(Graphics& gfx);
private:
	int x = 0;
	int y = 0;
};