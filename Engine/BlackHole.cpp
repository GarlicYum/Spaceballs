#include "BlackHole.h"

BlackHole::BlackHole(float X, AnimationFrames & bHoleAnim)
	:
	x(X),
	bHoleSpin(bHoleAnim, 5)
{}

void BlackHole::Reset()
{
	y = -50.0f;
}

void BlackHole::Update(float dt)
{
	y += vy * dt;
	bHoleSpin.Advance();
	if (bHoleSpin.AnimEnd())
	{
		bHoleSpin.Reset();
	}
}

void BlackHole::Draw(Graphics& gfx)
{
	bHoleSpin.Draw(int(x), int(y), gfx);
}

RectF BlackHole::GetCollisionRect() const
{
	return RectF(x, y, width, height);
}
