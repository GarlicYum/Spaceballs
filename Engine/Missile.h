#pragma once

#include "Graphics.h"
#include "Animation.h"
#include "Vec2.h"
#include "RectF.h"

class Missile
{
public:
	Missile();
	void Draw();
	void Update();

private:
	AnimationFrames missileFrames;
	Animation missileAnim;

	Vec2 pos;
	Vec2 vel;
	float accel = 0.2f;

	float angle;
	float angVel;
	float anfAccel = 0.01f;
};