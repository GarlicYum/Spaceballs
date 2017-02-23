#include "BlackHoleLevel.h"

BlackHoleLevel::BlackHoleLevel(AnimationFrames & background)
	:
	backGround(background, 2)
{}

void BlackHoleLevel::Draw(Graphics & gfx)
{
	backGround.Draw(0, 0, gfx);
}

void BlackHoleLevel::Update()
{
	backGround.Advance();
	if (backGround.AnimEnd())
	{
		backGround.Reset();
	}
}

RectF BlackHoleLevel::GetCollisionRect()
{
	return RectF(holePos, dimension, dimension);
}
