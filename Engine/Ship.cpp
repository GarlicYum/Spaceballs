#include "MainWindow.h"
#include "Ship.h"
#include "Surface.h"

Ship::Ship(BulletManager& Manager, Surface& ShipSurface, 
	Surface& red, AnimationFrames& shiprekt, AnimationFrames& holeAnim, 
	AnimationFrames& holeRektAnim, AnimationFrames& shipexplo, AnimationFrames& exhaustAnim, 
	AnimationFrames& rektExhaustAnim, Sound& shipexplodesound, Sound& blackholesound)
	:
	bManager(Manager),
	shipSurface(ShipSurface),
	redSurface(red), 
	shipRekt(shiprekt, 2),
	blackHole(holeAnim, 1),
	blackHoleRekt(holeRektAnim, 1),
	shipExplo(shipexplo, 2),
	exhaust(exhaustAnim, 2),
	rektExhaust(rektExhaustAnim, 2),
	shipExplodeSound(shipexplodesound),
	blackHoleSound(blackholesound)
{}

void Ship::HandleCollision(int Damage)
{
	switch (state)
	{
	case BlackHoleState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Advance();
		}
		else
		{
			blackHoleRekt.Advance();
		}

		if (blackHole.AnimEnd() || blackHoleRekt.AnimEnd())
		{
			state = DeadState;
		}
		break;

	case AliveState:
		health.Damage(Damage);
		isHit = true;
		break;
	}	
}

void Ship::Draw(Graphics& gfx)
{
	switch (state)
	{
	case AliveState:
		if (health.GetHealthAmount() > lowHealth)
		{
			if (!isMoving)
			{
				gfx.DrawSpriteKey(int(pos.x), int(pos.y), shipSurface, shipSurface.GetPixel(0, 0));
			}
			
			else
			{
				exhaust.Draw(int(pos.x), int(pos.y), gfx);
			}
		}

		else
		{
			if (!isMoving)
			{
				shipRekt.Draw(int(pos.x), int(pos.y), gfx);
			}

			else
			{
				rektExhaust.Draw(int(pos.x), int(pos.y), gfx);
			}
		}

		if (isHit)
		{
			gfx.DrawSpriteKey(int(pos.x), int(pos.y), redSurface, redSurface.GetPixel(0, 0));
		}
		break;

	case BlackHoleState:
		if (health.GetHealthAmount() > lowHealth)
		{
			blackHole.Draw(int(pos.x), int(pos.y), gfx);
		}

		else
		{
			blackHoleRekt.Draw(int(pos.x), int(pos.y), gfx);
		}
		break;

	case ExplodingState:
		shipExplo.Draw(int(pos.x) - exploX, int(pos.y) - exploY, gfx);
		break;
	}	

	health.Draw(gfx);
	bManager.DrawBullets(gfx);
}

void Ship::ClampScreen()
{
	pos.x = std::max(0.f, std::min(pos.x, float(Graphics::ScreenWidth) - (width + 1.f)));
	pos.y = std::max(0.f, std::min(pos.y, float(Graphics::ScreenHeight) - (height + 1.f)));
}

void Ship::PlayerInput(Keyboard& kbd, float dt)
{
	if (state == AliveState)
	{
		if (kbd.KeyIsPressed(VK_UP))
		{
			pos.y -= speed * dt;
			isMoving = true;
		}

		else if (kbd.KeyIsPressed(VK_DOWN))
		{
			pos.y += speed * dt;
			isMoving = false;
		}

		else
		{
			isMoving = false;
		}

		if (kbd.KeyIsPressed(VK_LEFT))
		{
			pos.x -= speed * dt;
		}

		else if (kbd.KeyIsPressed(VK_RIGHT))
		{
			pos.x += speed * dt;
		}

		if (kbd.KeyIsPressed(VK_SPACE))
		{
			bManager.FireBullet(Vec2(pos.x + canonX, pos.y + canonY));
		}

		else
		{
			bManager.ResetShotsFired();
		}
	}
}

void Ship::Restore(int restore)
{
	health.Restore(restore);
}

bool Ship::IsAlive() const
{
	return state == AliveState;
}

bool Ship::IsDead() const
{
	return state == DeadState;
}

RectF Ship::GetCollisionRect()
{
	return RectF(pos, width, height);
}

float Ship::GetX() const
{
	return pos.x;
}

float Ship::GetWidth() const
{
	return width;
}

float Ship::GetY() const
{
	return pos.y;
}

float Ship::GetHeight() const
{
	return height;
}

int Ship::GetHealth() const
{
	return health.GetHealthAmount();
}

void Ship::SethitTarget(bool hit)
{
	hitTarget = hit;
}

void Ship::AddGravity(Vec2 & gravity)
{
	pos -= gravity;
}

void Ship::SetY(float Y)
{
	pos.y = Y;
}

void Ship::SetX(float X)
{
	pos.x = X;
}

int Ship::GetDmg() const
{
	return dmg;
}

void Ship::CollidesWithHole(bool collides)
{
	if (collides && state == AliveState)
	{
		blackHoleSound.Play(0.8f, 1.0f);
		state = BlackHoleState;
	}	
}

void Ship::Reset()
{
	pos.x = 300.0f;
	pos.y = 300.0f;
	health.Reset();
	isHit = false;
	blackHole.Reset();
	blackHoleRekt.Reset();
	shipExplo.Reset();
	state = AliveState;
}

void Ship::Update(Keyboard & wnd, float dt)
{
	switch (state)
	{
	case AliveState:
		PlayerInput(wnd, dt);
		ClampScreen();

		if (pos.y + 2 > Graphics::ScreenHeight)
		{
			state = DeadState;
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

		if (health.GetHealthAmount() <= lowHealth)
		{
			if (!isMoving)
			{
				shipRekt.Advance();
				if (shipRekt.AnimEnd())
				{
					shipRekt.Reset();
				}
			}
			else
			{
				rektExhaust.Advance();
				if (rektExhaust.AnimEnd())
				{
					rektExhaust.Reset();
				}
			}
		}

		else if (isMoving)
		{
			exhaust.Advance();
			if (exhaust.AnimEnd())
			{
				exhaust.Reset();
			}
		}

		if (!health.HasHealth())
		{
			shipExplodeSound.Play();
			state = ExplodingState;
		}
		break;

	case ExplodingState:
		shipExplo.Advance();
		if (shipExplo.AnimEnd())
		{
			state = DeadState;
		}
		break;
	}
}
