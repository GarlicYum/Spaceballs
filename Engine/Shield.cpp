#include "Shield.h"
#include "Ship.h"

void Shield::Update(Ship& ship, Sound& shieldon, Sound& shieldoff)
{
	if (sState == NewState || sState == ActiveState)
	{
		const auto shipRect = ship.GetCollisionRect();
		pos.x = shipRect.GetCenterX();
		pos.y = shipRect.GetCenterY();
	}

	switch(sState)
	{
	case NewState:
		shieldon.Play(0.9f, 1.1f);
		meterWidth = 300;
		sState = ActiveState;
	break;
	case ActiveState:
		
		if (meterWidth <= 0)
		{
			sState = NoShield;
			shieldoff.Play(0.9f, 1.1f);
			shieldSize = 0.0f;
			holeSize = -5.0f;
		}
		if (shieldSize < radius)
		{
			shieldSize += 0.5;
			holeSize += 0.5;
		}
		break;
	}
}

void Shield::Draw(Graphics& gfx) const
{
	if (sState == ActiveState)
	{
		gfx.DrawAnnulus(int(pos.x), int(pos.y), int(shieldSize), int(holeSize), c);
		DrawMeter(gfx);
	}
}

void Shield::DrawMeter(Graphics& gfx) const
{
	gfx.DrawSquare(meterX, meterY, meterWidth, meterHeight, c);
}

bool Shield::GetisActive() const
{
	return sState == ActiveState;
}

void Shield::SetisActive(bool active)
{
	if (sState == NoShield)
	{
		sState = NewState;
	}
	else if (sState == NewState)
	{
		sState = ActiveState;
	}
}

RectF Shield::GetCollisionRect() const
{
	return RectF(
		Vec2(pos.x - radius, pos.y - radius),
		(radius * 2.0f),
		(radius * 2.5f));
}

int Shield::GetDmg() const
{
	return dmg;
}

void Shield::Reset()
{
	sState = NoShield;
}

void Shield::HandleCollision(int damage)
{
	meterWidth -= damage;
}

