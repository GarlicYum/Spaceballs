#include "SmallShield.h"

void SmallShield::Draw(Graphics & gfx)
{
	if (!isObtained)
	{
		gfx.DrawAnnulus(int(x), int(y), radius, hole, c);
	}
}

void SmallShield::Update(Ship& ship, float dt, Shield& shield)
{
	if (!isObtained)
	{
		y += vy * dt;
	}
}

RectF SmallShield::GetCollisionRect() const
{
	return RectF( x - radius, y - radius, radius * 2.f, radius * 2.f );
}

void SmallShield::HandleCollision( Shield& shield )
{
	if( !isObtained )
	{
		isObtained = true;
		shield.SetisActive( true );
	}
}

void SmallShield::SetPos(float X)
{
	x = X;
}
