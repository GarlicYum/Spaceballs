#include "MainWindow.h"
#include "Mine.h"
#include "Ship.h"
#include "Surface.h"

Mine::Mine( float X, const Surface & MineSurface, Sound &Explosion, AnimationFrames & Anim )
	:
	surface( MineSurface ),
	explo( Anim, 2 ),
	explosion( Explosion ),
	position( X, -50.f)
{}

void Mine::HandleCollision()
{
	switch( mState )
	{
		case MineState::ActiveState:
			damage = explDamage;
			SetState( Mine::DetonateState );
			explosion.Play();
			break;
		case MineState::DetonateState:
			damage = 0;
			break;
	}
}

//detects if the mine collides with a ship, passing in reference to the ship so mine knows its location
//returns a bool, this function will get called in mines update function

//updates the mine, takes ship as argument so it can call the detectcollision function
void Mine::Update( float Dt )
{
	switch( mState )
	{
		case MineState::ActiveState:
			position.y += vy * Dt;
			break;
		case MineState::DetonateState:
			//if mine is detonated it stops moving and explosion counter starts counting,
			//when the counter reaches explosion end then the explosion will no longer be displayed on screen
			explo.Advance();
			if( explo.AnimEnd() ) 
				mState = InActiveState;
			break;
	}
}

void Mine::Draw(Graphics& gfx)
{
	switch( mState )
	{
		case ActiveState:
			if( position.y < gfx.ScreenHeight )
			{
				gfx.DrawSpriteKey( int( position.x ), int( position.y ), surface, surface.GetPixel( 0, 0 ) );
			}
			break;
		case DetonateState:
			explo.Draw( int( position.x ), int( position.y ), gfx );
			break;
	}
}

int Mine::GetDamageCost() const
{
	return damage;
}

void Mine::SetState( MineState State )
{
	mState = State;
}

RectF Mine::GetCollisionRect() const
{
	return RectF( position, position + Vec2{width, height} );
}

bool Mine::IsActive() const
{
	return mState == ActiveState;
}

//float Mine::GetX() const
//{
//	return x;
//}
//
//float Mine::GetY() const
//{
//	return y;
//}
//
//float Mine::GetWidth() const
//{
//	return width;
//}
//
//float Mine::GetHeight() const
//{
//	return height;
//}


	

