#pragma once

#include "Graphics.h"
#include "Vec2.h"


class Star
{
public:
	Star();
	void Spawn(const Vec2 &Pos, float Size);
	void Update(float dt);
	void Draw(Graphics& gfx);
	void DrawBig(Graphics& gfx);
	
private:
	Vec2 position;
	float vy = 2.0f * 60.0f;
	float size;
};