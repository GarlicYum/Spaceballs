#pragma once

#include "Animation.h" 
#include "Graphics.h"
#include "RectF.h"
#include "Vec2.h"

class Comet
{
public:
	Comet(float pos_in, AnimationFrames& cometFrames);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetCollisionRect() const;
	void HandleCollision();
	void Reset();
	int GetDmg() const;
	bool IsActive() const;

private:
	Vec2 pos;
	static constexpr float vel = 200.0f;
	static constexpr float width = 35.0f;
	static constexpr float height = 80.0f;
	static constexpr int dmg = 50;
	Animation cometAnim;
	bool isActive = true;
};