#include "EnergyBoost.h"
#include "Surface.h"

EnergyBoost::EnergyBoost( float X, Sound & BoostSound, Surface & BoostSurface )
	:
	boostSound( BoostSound ),
	heart( BoostSurface ),
	x( X )
{}

void EnergyBoost::Update( Ship & ship, float dt )
{
	if( !isObtained )
	{
		y += vy * dt;
	}
}

void EnergyBoost::Draw(Graphics& gfx)
{
	if (!isObtained && y < Graphics::ScreenHeight )
	{		
		gfx.DrawSpriteKey(int(x), int(y), heart, heart.GetPixel(0, 0));
	}
}

RectF EnergyBoost::GetCollisionRect() const
{
	return RectF( x, y, width, height );
}

void EnergyBoost::HandleCollision( Ship & ship )
{
	isObtained = true;
	if( !isRestored )
	{
		boostSound.Play( 1.2f, 1.4f );
		ship.Restore( restoreAmount );
		isRestored = true;
	}
}
