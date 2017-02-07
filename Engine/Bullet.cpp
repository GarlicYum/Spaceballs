#include "Bullet.h"

//Anything I want to draw on screen should have an update function and a draw function

Bullet::Bullet( float X, float Y )
	:
	x( X ), y( Y ),
	bState( AliveState )
{}

void Bullet::Update(float dt)
{
	y -= vy * dt;

	if (y - bulletSize < 0) //if bullet reaches end of screen, hasspawned becomes false and bullet will no longer be drawn
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
	gfx.DrawCircle(int(x), int(y), bulletSize, Colors::Magenta);
}

bool Bullet::IsActive() const
{
	return bState == AliveState;
}

RectF Bullet::GetCollisionRect() const
{
	const float bSize = float( bulletSize );
	return RectF( 
		x - bSize, 
		y - bSize, 
		( bSize * 2.f), 
		( bSize * 2.f) );
}

void Bullet::HandleCollision()
{
	bState = DeadState;
}
