#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

Ship::Ship( BulletManager & Manager, Surface &ShipSurface )
	:
	bManager( Manager ),
	shipSurface( ShipSurface )
{}

void Ship::HandleCollision( int  Damage )
{
	health.Damage( Damage );
}

// draws the ship and draws spawned bullets and anything that has to do with ship
void Ship::Draw(Graphics& gfx) 
{	
	if (health.HasHealth())
	{
		gfx.DrawSpriteKey(int( position.x), int( position.y), shipSurface, shipSurface.GetPixel(0, 0));
		health.Draw(gfx);
		bManager.DrawBullets( gfx );
	}
}

void Ship::ClampScreen()
{
	position = Vec2(
		std::max( 0.f, std::min( position.x, float( Graphics::ScreenWidth ) - ( width + 1.f ) ) ),
		std::max( 0.f, std::min( position.y, float( Graphics::ScreenHeight ) - ( height + 1.f ) ) )
	);
}

// gets the player input
void Ship::PlayerInput( Keyboard & kbd, float dt)
{
	Vec2 vel( 0.f, 0.f );
	if (kbd.KeyIsPressed(VK_UP))
	{
		vel.y -= velocity.y;
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		vel.y += velocity.y;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		vel.x -= velocity.x;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		vel.x += velocity.x;
	}
	const float speed = velocity.Length();
	position += ( vel.Normalize() * ( speed * dt ) );
	
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		bManager.FireBullet( position + cannonOffset );
	}
	else
	{
		bManager.ResetShotsFired();
	}
}

void Ship::Restore(int restore)
{
	health.Restore(restore);
}

bool Ship::HasHealth() const
{
	return health.HasHealth();
}

RectF Ship::GetCollisionRect() const
{
	return RectF( position, position + Vec2{ width, height } );
}

void Ship::SethitTarget(bool hit)
{
	hitTarget = hit;
}

// updates should be neat. we use player input function
// this way we can easily shut off player input if there's a cutscene etc
void Ship::Update( Keyboard & wnd, float dt)
{
	if (HasHealth())
	{
		PlayerInput(wnd, dt);		
		ClampScreen();
	}	
}

