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
		if (DetectCollision(ship))
		{
			isObtained = true;
			shield.SetisActive(true);
		}
	}
}

bool SmallShield::DetectCollision(Ship & ship)
{
	const float ssRight = x + radius;
	const float ssBottom = y + radius;
	const float ssLeft = x - radius;
	const float ssTop = y - radius;
	const float sRight = ship.GetWidth() + ship.GetX();
	const float sBottom = ship.GetHeight() + ship.GetY();

	return
		ssRight >= ship.GetX() &&
		ssLeft <= sRight &&
		ssBottom >= ship.GetY() &&
		ssTop <= sBottom;
}

void SmallShield::SetPos(float X)
{
	x = X;
}
