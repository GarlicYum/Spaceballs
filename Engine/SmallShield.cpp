#include "SmallShield.h"

void SmallShield::Draw(Graphics & gfx)
{
	if (!isObtained)
	{
		gfx.DrawAnnulus(int(pos.x), int(pos.y), radius, hole, c);
	}
}

void SmallShield::Update(Ship& ship, float dt, Shield& shield)
{
	if (!isObtained)
	{
		pos.y += vy * dt;
	}
}

RectF SmallShield::GetCollisionRect() const
{
	return RectF(Vec2(pos.x - radius, pos.y - radius), radius * 2.f, radius * 2.f);
}

void SmallShield::HandleCollision(Shield& shield)
{
	if (!isObtained)
	{
		isObtained = true;
		shield.SetisActive(true);
	}
}

void SmallShield::SetPos(float X)
{
	pos.x = X;
}

void SmallShield::Reset()
{
	pos.y = -40.0f;
}
