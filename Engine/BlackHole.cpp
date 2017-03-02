#include "BlackHole.h"

BlackHole::BlackHole(float X, AnimationFrames & bHoleAnim)
	:
	pos(X, -50.0f),
	bHoleSpin(bHoleAnim, 5.0f)
{}

void BlackHole::Reset()
{
	pos.y = -50.0f;
	vy = resetVy;
	isActive = true;
}

void BlackHole::Update(float dt)
{
	if (pos.y + height > 0.0f && pos.y < Graphics::ScreenHeight)
	{
		pos.y += vy * dt;
		bHoleSpin.Advance(dt);
		if (bHoleSpin.AnimEnd())
		{
			bHoleSpin.Reset();
		}
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

void BlackHole::Deactivate()
{
	isActive = false;
}

void BlackHole::StopVy()
{
	vy = 0.0f;
}

void BlackHole::StartVy()
{
	vy = 80.0f;
}
