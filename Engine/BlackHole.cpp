#include "BlackHole.h"

BlackHole::BlackHole(float X, AnimationFrames & bHoleAnim)
	:
	x(X),
	bHoleSpin(bHoleAnim, 5)
{}

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
