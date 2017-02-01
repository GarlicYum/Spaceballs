#pragma once
#include "Graphics.h"

class Bullet
{
public:
	void Spawn(float X, float Y, float dt);
	void Update(float dt);
	bool HasSpawned() const;
	void Draw(Graphics & gfx);
	float GetX() const;
	float GetY() const;
	int GetBulletSize() const;
	void SetHasSpawned(bool hit);
	
private:
	bool hasSpawned = false;
	int bulletSize = 10;
	float x;
	float y;
	float vy = 15.0f * 60.0f;
	static constexpr int dmg = 20;
};