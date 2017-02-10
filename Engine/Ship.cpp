#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

Ship::Ship(BulletManager& Manager, Surface& ShipSurface, Surface& exhaust, Surface& red)
	:
	bManager(Manager),
	shipSurface(ShipSurface),
	exhaustSurface(exhaust),
	redSurface(red)
{}

void Ship::HandleCollision(int Damage)
{
	health.Damage(Damage);
	isHit = true;
}

void Ship::Draw(Graphics& gfx)
{
	if (health.HasHealth())
	{
		gfx.DrawSpriteKey(int(x), int(y), shipSurface, shipSurface.GetPixel(0, 0));
		
		if (isMoving)
		{
			gfx.DrawSpriteKey(int(x), int(y), exhaustSurface, exhaustSurface.GetPixel(0, 0));
		}

		if (isHit)
		{
			gfx.DrawSpriteKey(int(x), int(y), redSurface, redSurface.GetPixel(0, 0));
		}
		health.Draw(gfx);
		bManager.DrawBullets(gfx);
	}
}

void Ship::ClampScreen()
{
	x = std::max(0.f, std::min(x, float(Graphics::ScreenWidth) - (width + 1.f)));
	y = std::max(0.f, std::min(y, float(Graphics::ScreenHeight) - (height + 1.f)));
}

void Ship::PlayerInput(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_UP))
	{
		y -= vy * dt;
		isMoving = true;
	}

	else if (kbd.KeyIsPressed(VK_DOWN))
	{
		y += vy * dt;
		isMoving = false;
	}

	else
	{
		isMoving = false;
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
		bManager.FireBullet(x + canonX, y + canonY, dt);
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
	return RectF(x, y, width, height);
}

float Ship::GetX() const
{
	return x;
}

float Ship::GetWidth() const
{
	return width;
}

float Ship::GetY() const
{
	return y;
}

float Ship::GetHeight() const
{
	return height;
}

void Ship::SethitTarget(bool hit)
{
	hitTarget = hit;
}

void Ship::SetY(float Y)
{
	y = Y;
}

void Ship::SetX(float X)
{
	x = X;
}

int Ship::GetDmg() const
{
	return dmg;
}

void Ship::Reset()
{
	x = 300.0f;
	y = 300.0f;
	health.Reset();
	isHit = false;
	isMoving = false;
}

void Ship::Update(Keyboard & wnd, float dt)
{
	if (y + 2 > Graphics::ScreenHeight)
	{
		health.Damage(health.GetHealthAmount());
	}
	if (HasHealth())
	{
		PlayerInput(wnd, dt);
		ClampScreen();
	}
	if (isHit)
	{
		isHitCounter++;
		if (isHitCounter >= 10)
		{
			isHitCounter = 0;
			isHit = false;
		}
	}
}