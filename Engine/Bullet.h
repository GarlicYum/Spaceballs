#pragma once
#include "Graphics.h"

class Bullet
{
public:
	void Spawn(float X, float Y, float dt);
	void Update(float dt);
	bool HasSpawned() const;
	void Draw(Graphics & gfx);
private:
	int bulletSize = 10;
	float x;
	float y;
	float vy = 15.0f * 60.0f;
	bool hasSpawned = false;
};