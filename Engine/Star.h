#pragma once
#include "Graphics.h"
#include <random>
#include "Vec2.h"

class Star
{
public:
	Star();
	void Spawn(Vec2& pos_in, float Size);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void DrawBig(Graphics& gfx);
	
private:
	Vec2 pos;
	float vy = 2.0f * 60.0f;
	float size;
};