#pragma once
#include "Graphics.h"

class Star
{
public:
	void Spawn(int X, int Y, int Size);
	void Update();
	void Draw(Graphics& gfx);
	void DrawBig(Graphics& gfx);
	
private:
	int x;
	int y;
	int size;
};