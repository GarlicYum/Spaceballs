#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

// draws the ship and draws spawned bullets and anything that has to do with ship
void Ship::Draw(Graphics& gfx) 
{
	
	if (health.HasHealth())
	{
		static const Surface ship = Surface::FromFile(L"shippit.png");

		gfx.DrawSpriteKey(int(x), int(y), ship, ship.GetPixel(0, 0));
		
		for (int i = 0; i < nBullets; i++)
		{
			if (bullet[i].HasSpawned())
			{
				bullet[i].Draw(gfx);
			}
		}
		health.Draw(gfx);
	}
}

void Ship::FireBullet(float dt)
{
	if (shotsFired == false)
	{
		for (int i = 0; i < nBullets; ++i)
		{
			if (!bullet[i].HasSpawned())
			{
				bullet[i].Spawn(x + canonX, y +canonY, dt);
				gun.Play(0.5F, 0.5F);
				shotsFired = true;
				break;
			}
		}
	}
}

void Ship::ClampScreen()
{
	float right = x + width;
	float bottom = y + height;
	if (x < 0)
	{
		x = 0;
	}
	if (right >= Graphics::ScreenWidth)
	{
		x = float(Graphics::ScreenWidth) - width;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (bottom >= Graphics::ScreenHeight - padding)
	{
		y = float(Graphics::ScreenHeight) - height - padding;
	}
}

// gets the player input
void Ship::PlayerInput(MainWindow & wnd, float dt)
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		y -= vy * dt;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		y += vy * dt;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		x -= vx * dt;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		x += vx * dt;
	}
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		FireBullet(dt);
	}
	else
	{
		shotsFired = false;
	}
}

void Ship::Restore(int restore)
{
	health.Restore(restore);
}

//gets called when a mine is detonated
void Ship::Damage(int damage)
{
	health.Damage(damage);
}

bool Ship::HasHealth() const
{
	return health.HasHealth();
}

float Ship::GetX() 
{
	return x;
}

float Ship::GetY() 
{
	return y;
}

float Ship::GetWidth() 
{
	return width;
}

float Ship::GetHeight() 
{
	return height;
}

Bullet* Ship::GetBullets()
{
	return bullet;
}

int Ship::GetnBullets()
{
	return nBullets;
}

void Ship::SethitTarget(bool hit)
{
	hitTarget = hit;
}

// updates should be neat. we use player input function
// this way we can easily shut off player input if there's a cutscene etc
void Ship::Update(MainWindow & wnd, float dt)
{

	if (HasHealth())
	{
		PlayerInput(wnd, dt);

		for (int i = 0; i < nBullets; i++)
		{
			if (bullet[i].HasSpawned())
			{
				bullet[i].Update(dt);
			}
		}

		ClampScreen();
	}
	
}

