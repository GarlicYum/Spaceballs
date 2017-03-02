#include "Comet.h"

Comet::Comet(float pos_in, AnimationFrames & cometFrames)
	:
	pos(pos_in, -80.0f),
	cometAnim(cometFrames, 2.0f)
{}

void Comet::Draw(Graphics & gfx) 
{
	if (isActive)
	{
		cometAnim.Draw(int(pos.x), int(pos.y), gfx);
	}
}

void Comet::Update(float dt)
{
	if (pos.y > Graphics::ScreenHeight)
	{
		isActive = false;
	}
	if (isActive)
	{
		pos.y += (vel * dt);
		cometAnim.Advance(dt);
		if (cometAnim.AnimEnd())
		{
			cometAnim.Reset();
		}
	}
}

RectF Comet::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void Comet::HandleCollision()
{
	isActive = false;
}

void Comet::Reset()
{
	pos.y = -80.0f;
	isActive = true;
}

int Comet::GetDmg() const
{
	return dmg;
}

bool Comet::IsActive() const
{
	return isActive;
}
