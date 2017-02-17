#include "EnergyBoost.h"
#include "Surface.h"

EnergyBoost::EnergyBoost(float X, Sound& BoostSound, Surface& BoostSurface)
	:
	boostSound(BoostSound),
	heart(BoostSurface),
	pos(X, resetY)
{}

void EnergyBoost::Update(Ship& ship, float dt)
{
	if (!isObtained)
	{
		pos.y += vy * dt;
	}
}

void EnergyBoost::Draw(Graphics& gfx)
{
	if (!isObtained && pos.y < Graphics::ScreenHeight)
	{
		gfx.DrawSpriteKey(int(pos.x), int(pos.y), heart, heart.GetPixel(0, 0));
	}
}

RectF EnergyBoost::GetCollisionRect() const
{
	return RectF(pos, width, height);
}

void EnergyBoost::HandleCollision(Ship& ship)
{
	isObtained = true;
	if (!isRestored)
	{
		boostSound.Play(1.2f, 1.4f);
		ship.Restore(restoreAmount);
		isRestored = true;
	}
}

void EnergyBoost::Reset()
{
	pos.y = resetY;
	isObtained = false;
	isRestored = false;
}
