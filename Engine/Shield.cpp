#include "Shield.h"
#include "Ship.h"


Shield::Shield()
{
}

void Shield::Update(Ship & ship, Sound& shieldon, Sound& shieldoff)
{
	switch( sState )
	{
		case NewState:
			shieldon.Play( 0.9f, 1.1f );
			meterWidth = 300;
			sState = ActiveState;
			break;
		case ActiveState:
			const auto shipRect = ship.GetCollisionRect();
			x = shipRect.GetCenterX();
			y = shipRect.GetCenterY();

			meterCounter++;
			if( meterCounter == meterDecrease )
			{
				meterCounter = 0;
				meterWidth--;
			}

			if( meterWidth <= 0 )
			{
				sState = NoShield;
				shieldoff.Play( 0.9f, 1.1f );
				shieldSize = 0;
				holeSize = -5;
			}
			if( shieldSize < radius )
			{
				shieldSize += 5;
				holeSize += 5;
			}
			break;
	}
}

void Shield::Draw(Graphics& gfx)const
{
	if( sState == ActiveState )
	{
		gfx.DrawAnnulus( int( x ), int( y ), shieldSize, holeSize, c );
		DrawMeter( gfx );
	}
}

void Shield::DrawMeter(Graphics& gfx)const
{
	gfx.DrawSquare(meterX, meterY, meterWidth, meterHeight, c);
}

bool Shield::GetisActive() const
{
	return sState == ActiveState;
}

void Shield::SetisActive(bool active)
{
	if( sState == NoShield )
	{
		sState = NewState;
	}
	else if( sState == NewState )
	{
		sState = ActiveState;
	}
}

RectF Shield::GetCollisionRect() const
{
	return RectF(
		x - radius,
		y - radius,
		(radius * 2.f),
		(radius * 2.f) );
}
