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
	if (pos.y + height > 0.0f && pos.y < Graphics::ScreenHeight)
	{
		isActive = true;
	}
	else
	{
		isActive = false;
	}
}

void BlackHole::Draw(Graphics& gfx)
{
	bHoleSpin.Draw(int(pos.x), int(pos.y), gfx);
}

RectF BlackHole::GetCollisionRect() const
{
	return RectF(Vec2(pos.x - range, pos.y - range), width + range*2, height + range*2);
}

bool BlackHole::GetIsActive() const
{
	return isActive;
}
