#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

Ship::Ship(BulletManager& Manager, Surface& ShipSurface)
	:
	bManager(Manager),
	shipSurface(ShipSurface)
{}

void Ship::HandleCollision(int Damage)
{
	health.Damage(Damage);
}

void Ship::Draw(Graphics& gfx)
{
	if (health.HasHealth())
	{
		gfx.DrawSpriteKey(int(x), int(y), shipSurface, shipSurface.GetPixel(0, 0));
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

void Ship::Update(Keyboard & wnd, float dt)
{
	if (y + 1 > Graphics::ScreenHeight)
	{
		health.Damage(health.GetHealthAmount());
	}
	if (HasHealth())
	{
		PlayerInput(wnd, dt);
		ClampScreen();
	}
}