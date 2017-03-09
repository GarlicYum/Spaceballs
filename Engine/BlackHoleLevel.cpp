#include "BlackHoleLevel.h"

BlackHoleLevel::BlackHoleLevel(AnimationFrames & background, AnimationFrames& CometAnim)
	:
	backGround(background, 2.0f),
	cometAnim(CometAnim)
{}

void BlackHoleLevel::Draw(Graphics & gfx)
{
	backGround.Draw(0, 0, gfx);
	for (int i = 0; i < nComets; ++i)
	{
		if (!comet[i].IsActive())
			continue;
		else
			comet[i].Draw(gfx);
	}
}

void BlackHoleLevel::Update(float dt)
{
	backGround.Advance(dt);
	if (backGround.AnimEnd())
	{
		backGround.Reset();
	}

	for (int i = 0; i < nComets; ++i)
	{
		if (!comet[i].IsActive())
			continue;
		else
			comet[i].Update(dt);
	}
}

RectF BlackHoleLevel::GetCollisionRect()
{
	return RectF(holePos, dimension, dimension);
}

Comet & BlackHoleLevel::GetComet(int Idx)
{
	return comet[Idx];
}

const Comet & BlackHoleLevel::GetComet(int Idx) const
{
	return comet[Idx];
}

int BlackHoleLevel::GetCometCount() const
{
	return nComets;
}

void BlackHoleLevel::Reset()
{
	for (int i = 0; i < nComets; ++i)
	{
		comet[i].Reset();
	}
}

void BlackHoleLevel::Spawn(float X, float Y)
{
	nComets++;
	comet.emplace_back<Comet>(Comet{ X, Y, cometAnim });
}
