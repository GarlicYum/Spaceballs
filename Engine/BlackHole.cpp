#include "BlackHole.h"

BlackHole::BlackHole(float X, AnimationFrames & bHoleAnim)
	:
	pos(X, -50.0f),
	bHoleSpin(bHoleAnim, 5)
{}

void BlackHole::Reset()
{
	pos.y = -50.0f;
}

void BlackHole::Update(float dt)
{
	pos.y += vy * dt;
	bHoleSpin.Advance();
	if (bHoleSpin.AnimEnd())
	{
		bHoleSpin.Reset();
	}
}

void BlackHole::Draw(Graphics& gfx)
{
	bHoleSpin.Draw(int(pos.x), int(pos.y), gfx);
}

RectF BlackHole::GetCollisionRect() const
{
	return RectF(pos, width, height);
}
