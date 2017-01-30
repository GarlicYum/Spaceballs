#pragma once
#include "Graphics.h"

class Star
{
public:
	void Spawn(float X, float Y, float Size);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void DrawBig(Graphics& gfx);
	
private:
	float x;
	float y;
	float vy = 1.0f * 60.0f;
	float size;
};