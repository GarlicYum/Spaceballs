#include "EnergyBoost.h"
#include "Surface.h"

void EnergyBoost::Draw(Graphics& gfx)
{
	if (!isObtained && y < gfx.ScreenHeight)
	{
		static const Surface heart = Surface::FromFile(L"hart.png");
		gfx.DrawSpriteKey(int(x), int(y), heart, heart.GetPixel(0, 0));
	}
}

bool EnergyBoost::DetectCollision(Ship & ship)
{
	const float eRight = x + width;
	const float eBottom = y + height;
	const float sRight = ship.GetWidth() + ship.GetX();
	const float sBottom = ship.GetHeight() + ship.GetY();

	return
		eRight >= ship.GetX() &&
		x <= sRight &&
		eBottom >= ship.GetY() &&
		y <= sBottom;
}

void EnergyBoost::Update(Ship & ship, float dt)
{
	if (!isObtained)
	{
		y += vy * dt;
		if (DetectCollision(ship))
		{
			isObtained = true;
			if (!isRestored)
			{
				boostSound.Play(1.2f, 1.4f);
				ship.Restore(restoreAmount);
				isRestored = true;
			}

		}
	}
	
}

void EnergyBoost::SetPos(float X)
{
	x = X;
}
