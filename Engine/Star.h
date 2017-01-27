#pragma once
#include "Graphics.h"

class Star
{
public:
	void DrawSmall(Graphics& gfx, int x, int y);
	void DrawMid(Graphics& gfx);
	void DrawBig(Graphics& gfx);
	int x;
	int y;
private:

};