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
		gfx.DrawSpriteKey(int(x), int(y), shipSurface, shipSurface.GetPixel(0, 0));
		health.Draw(gfx);
		bManager.DrawBullets( gfx );
	}
}

void Ship::ClampScreen()
{
	x = std::max( 0.f, std::min( x, float( Graphics::ScreenWidth ) - ( width + 1.f ) ) );
	y = std::max( 0.f, std::min( y, float( Graphics::ScreenHeight ) - ( height + 1.f ) ) );
}

// gets the player input
void Ship::PlayerInput( Keyboard & kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		y -= vy * dt;
	}
	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		y += vy * dt;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		x -= vx * dt;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		x += vx * dt;
	}
	if (kbd.KeyIsPressed(VK_SPACE))
	{
		bManager.FireBullet( x + canonX, y + canonY, dt );
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
	return RectF( x, y, width, height );
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

