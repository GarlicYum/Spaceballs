#include "Bullet.h"

//Anything I want to draw on screen should have an update function and a draw function

Bullet::Bullet( const Vec2 &CannonPosition )
	:
	position( CannonPosition ),
	bState( AliveState )
{}

void Bullet::Update(float dt)
{
	position.y -= ( vy * dt );

	if ( position.y - bulletSize < 0) //if bullet reaches end of screen, hasspawned becomes false and bullet will no longer be drawn
	{
		bState = DeadState;
	}
}

bool Bullet::HasSpawned() const
{
	return bState == AliveState;
}

void Bullet::Draw(Graphics& gfx)
{	
	gfx.DrawCircle(int( position.x), int( position.y), bulletSize, Colors::Magenta);
}

bool Bullet::IsActive() const
{
	return bState == AliveState;
}

RectF Bullet::GetCollisionRect() const
{
	const float bSize = float( bulletSize );
	const Vec2 vSize( bSize, bSize );
	return RectF(
		position - vSize,
		position + vSize );
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}
